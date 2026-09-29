#ifndef QELFORMRULE_H
#define QELFORMRULE_H

#include <QRegularExpression>
#include <QString>

#include <functional>

namespace qel {

struct QelFormRule
{
    bool required = false;
    int minLength = -1;
    int maxLength = -1;
    QRegularExpression pattern;
    QString message;
    std::function<bool(const QString &, QString &)> validator;

    static QelFormRule requiredRule(const QString &message = QString())
    {
        QelFormRule rule;
        rule.required = true;
        rule.message = message;
        return rule;
    }

    static QelFormRule lengthRule(int minLength,
                                  int maxLength = -1,
                                  const QString &message = QString())
    {
        QelFormRule rule;
        rule.minLength = minLength;
        rule.maxLength = maxLength;
        rule.message = message;
        return rule;
    }

    static QelFormRule patternRule(const QRegularExpression &pattern,
                                   const QString &message = QString())
    {
        QelFormRule rule;
        rule.pattern = pattern;
        rule.message = message;
        return rule;
    }

    static QelFormRule customRule(
        const std::function<bool(const QString &, QString &)> &validator,
        const QString &message = QString())
    {
        QelFormRule rule;
        rule.validator = validator;
        rule.message = message;
        return rule;
    }
};

} // namespace qel

#endif // QELFORMRULE_H
