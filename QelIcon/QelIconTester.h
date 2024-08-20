#ifndef QELICONTESTER_H
#define QELICONTESTER_H

#include "QelIcon.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QFontDatabase>
#include <QChar>
#include <QScrollArea>

using namespace qel;


class QelIconTester : public QWidget {
public:
    QelIconTester(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

                // 创建一个滚动区域
        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);

        QWidget *scrollWidget = new QWidget();
        QGridLayout *layout = new QGridLayout(scrollWidget);

        int row = 0;
        int col = 0;

        struct IconData {
            QString name;
            QelIcon::Icon icon;
        };

                // 定义所有 FontAwesome 图标的枚举值及其名称
        IconData icons[] = {
            {"Glass", QelIcon::Glass},
            {"Music", QelIcon::Music},
            {"Search", QelIcon::Search},
            {"EnvelopeO", QelIcon::EnvelopeO},
            {"Heart", QelIcon::Heart},
            {"Star", QelIcon::Star},
            {"StarO", QelIcon::StarO},
            {"User", QelIcon::User},
            {"Film", QelIcon::Film},
            {"ThLarge", QelIcon::ThLarge},
            {"Th", QelIcon::Th},
            {"ThList", QelIcon::ThList},
            {"Check", QelIcon::Check},
            {"Close", QelIcon::Close},
            {"SearchPlus", QelIcon::SearchPlus},
            {"SearchMinus", QelIcon::SearchMinus},
            {"PowerOff", QelIcon::PowerOff},
            {"Signal", QelIcon::Signal},
            {"Cog", QelIcon::Cog},
            {"TrashO", QelIcon::TrashO},
            {"Home", QelIcon::Home},
            {"FileO", QelIcon::FileO},
            {"ClockO", QelIcon::ClockO},
            {"Road", QelIcon::Road},
            {"Download", QelIcon::Download},
            {"ArrowCircleODown", QelIcon::ArrowCircleODown},
            {"ArrowCircleOUp", QelIcon::ArrowCircleOUp},
            {"Inbox", QelIcon::Inbox},
            {"PlayCircleO", QelIcon::PlayCircleO},
            {"Repeat", QelIcon::Repeat},
            {"Refresh", QelIcon::Refresh},
            {"ListAlt", QelIcon::ListAlt},
            {"Lock", QelIcon::Lock},
            {"Flag", QelIcon::Flag},
            {"Headphones", QelIcon::Headphones},
            {"VolumeOff", QelIcon::VolumeOff},
            {"VolumeDown", QelIcon::VolumeDown},
            {"VolumeUp", QelIcon::VolumeUp},
            {"Qrcode", QelIcon::Qrcode},
            {"Barcode", QelIcon::Barcode},
            {"Tag", QelIcon::Tag},
            {"Tags", QelIcon::Tags},
            {"Book", QelIcon::Book},
            {"Bookmark", QelIcon::Bookmark},
            {"Print", QelIcon::Print},
            {"Camera", QelIcon::Camera},
            {"Font", QelIcon::Font},
            {"Bold", QelIcon::Bold},
            {"Italic", QelIcon::Italic},
            {"TextHeight", QelIcon::TextHeight},
            {"TextWidth", QelIcon::TextWidth},
            {"AlignLeft", QelIcon::AlignLeft},
            {"AlignCenter", QelIcon::AlignCenter},
            {"AlignRight", QelIcon::AlignRight},
            {"AlignJustify", QelIcon::AlignJustify},
            {"List", QelIcon::List},
            {"Outdent", QelIcon::Outdent},
            {"Indent", QelIcon::Indent},
            {"VideoCamera", QelIcon::VideoCamera},
            {"PictureO", QelIcon::PictureO},
            {"Pencil", QelIcon::Pencil},
            {"MapMarker", QelIcon::MapMarker},
            {"Adjust", QelIcon::Adjust},
            {"Tint", QelIcon::Tint},
            {"PencilSquareO", QelIcon::PencilSquareO},
            {"ShareSquareO", QelIcon::ShareSquareO},
            {"CheckSquareO", QelIcon::CheckSquareO},
            {"Arrows", QelIcon::Arrows},
            {"StepBackward", QelIcon::StepBackward},
            {"FastBackward", QelIcon::FastBackward},
            {"Backward", QelIcon::Backward},
            {"Play", QelIcon::Play},
            {"Pause", QelIcon::Pause},
            {"Stop", QelIcon::Stop},
            {"Forward", QelIcon::Forward},
            {"FastForward", QelIcon::FastForward},
            {"StepForward", QelIcon::StepForward},
            {"Eject", QelIcon::Eject},
            {"ChevronLeft", QelIcon::ChevronLeft},
            {"ChevronRight", QelIcon::ChevronRight},
            {"PlusCircle", QelIcon::PlusCircle},
            {"MinusCircle", QelIcon::MinusCircle},
            {"TimesCircle", QelIcon::TimesCircle},
            {"CheckCircle", QelIcon::CheckCircle},
            {"QuestionCircle", QelIcon::QuestionCircle},
            {"InfoCircle", QelIcon::InfoCircle},
            {"Crosshairs", QelIcon::Crosshairs},
            {"TimesCircleO", QelIcon::TimesCircleO},
            {"CheckCircleO", QelIcon::CheckCircleO},
            {"Ban", QelIcon::Ban},
            {"ArrowLeft", QelIcon::ArrowLeft},
            {"ArrowRight", QelIcon::ArrowRight},
            {"ArrowUp", QelIcon::ArrowUp},
            {"ArrowDown", QelIcon::ArrowDown},
            {"Share", QelIcon::Share},
            {"Expand", QelIcon::Expand},
            {"Compress", QelIcon::Compress},
            {"Plus", QelIcon::Plus},
            {"Minus", QelIcon::Minus},
            {"Asterisk", QelIcon::Asterisk},
            {"ExclamationCircle", QelIcon::ExclamationCircle},
            {"Gift", QelIcon::Gift},
            {"Leaf", QelIcon::Leaf},
            {"Fire", QelIcon::Fire},
            {"Eye", QelIcon::Eye},
            {"EyeSlash", QelIcon::EyeSlash},
            {"Warning", QelIcon::Warning},
            {"ExclamationTriangle", QelIcon::ExclamationTriangle},
            {"Plane", QelIcon::Plane},
            {"Calendar", QelIcon::Calendar},
            {"Random", QelIcon::Random},
            {"Comment", QelIcon::Comment},
            {"Magnet", QelIcon::Magnet},
            {"ChevronUp", QelIcon::ChevronUp},
            {"ChevronDown", QelIcon::ChevronDown},
            {"Retweet", QelIcon::Retweet},
            {"ShoppingCart", QelIcon::ShoppingCart},
            {"Folder", QelIcon::Folder},
            {"FolderOpen", QelIcon::FolderOpen},
            {"ArrowsV", QelIcon::ArrowsV},
            {"ArrowsH", QelIcon::ArrowsH},
            {"BarChartO", QelIcon::BarChartO},
            {"TwitterSquare", QelIcon::TwitterSquare},
            {"FacebookSquare", QelIcon::FacebookSquare},
            {"CameraRetro", QelIcon::CameraRetro},
            {"Key", QelIcon::Key},
            {"Cogs", QelIcon::Cogs},
            {"Comments", QelIcon::Comments},
            {"ThumbsOUp", QelIcon::ThumbsOUp},
            {"ThumbsODown", QelIcon::ThumbsODown},
            {"StarHalf", QelIcon::StarHalf},
            {"HeartO", QelIcon::HeartO},
            {"SignOut", QelIcon::SignOut},
            {"LinkedinSquare", QelIcon::LinkedinSquare},
            {"ThumbTack", QelIcon::ThumbTack},
            {"ExternalLink", QelIcon::ExternalLink},
            {"SignIn", QelIcon::SignIn},
            {"Trophy", QelIcon::Trophy},
            {"GithubSquare", QelIcon::GithubSquare},
            {"Upload", QelIcon::Upload},
            {"LemonO", QelIcon::LemonO},
            {"Phone", QelIcon::Phone},
            {"SquareO", QelIcon::SquareO},
            {"BookmarkO", QelIcon::BookmarkO},
            {"PhoneSquare", QelIcon::PhoneSquare},
            {"Twitter", QelIcon::Twitter},
            {"Facebook", QelIcon::Facebook},
            {"Github", QelIcon::Github},
            {"Unlock", QelIcon::Unlock},
            {"CreditCard", QelIcon::CreditCard},
            {"Rss", QelIcon::Rss},
            {"HddO", QelIcon::HddO},
            {"Bullhorn", QelIcon::Bullhorn},
            {"Bell", QelIcon::Bell},
            {"Certificate", QelIcon::Certificate},
            {"HandORight", QelIcon::HandORight},
            {"HandOLeft", QelIcon::HandOLeft},
            {"HandOUp", QelIcon::HandOUp},
            {"HandODown", QelIcon::HandODown},
            {"ArrowCircleLeft", QelIcon::ArrowCircleLeft},
            {"ArrowCircleRight", QelIcon::ArrowCircleRight},
            {"ArrowCircleUp", QelIcon::ArrowCircleUp},
            {"ArrowCircleDown", QelIcon::ArrowCircleDown},
            {"Globe", QelIcon::Globe},
            {"Wrench", QelIcon::Wrench},
            {"Tasks", QelIcon::Tasks},
            {"Filter", QelIcon::Filter},
            {"Briefcase", QelIcon::Briefcase},
            {"ArrowsAlt", QelIcon::ArrowsAlt},
            {"Users", QelIcon::Users},
            {"Link", QelIcon::Link},
            {"Cloud", QelIcon::Cloud},
            {"Flask", QelIcon::Flask},
            {"Scissors", QelIcon::Scissors},
            {"FilesO", QelIcon::FilesO},
            {"Paperclip", QelIcon::Paperclip},
            {"Save", QelIcon::Save},
            {"Square", QelIcon::Square},
            {"Bars", QelIcon::Bars},
            {"ListUl", QelIcon::ListUl},
            {"ListOl", QelIcon::ListOl},
            {"Strikethrough", QelIcon::Strikethrough},
            {"Underline", QelIcon::Underline},
            {"Table", QelIcon::Table},
            {"Magic", QelIcon::Magic},
            {"Truck", QelIcon::Truck},
            {"Pinterest", QelIcon::Pinterest},
            {"PinterestSquare", QelIcon::PinterestSquare},
            {"GooglePlusSquare", QelIcon::GooglePlusSquare},
            {"GooglePlus", QelIcon::GooglePlus},
            {"Money", QelIcon::Money},
            {"CaretDown", QelIcon::CaretDown},
            {"CaretUp", QelIcon::CaretUp},
            {"CaretLeft", QelIcon::CaretLeft},
            {"CaretRight", QelIcon::CaretRight},
            {"Columns", QelIcon::Columns},
            {"Sort", QelIcon::Sort},
            {"SortAsc", QelIcon::SortAsc},
            {"SortDesc", QelIcon::SortDesc},
            {"Envelope", QelIcon::Envelope},
            {"Linkedin", QelIcon::Linkedin},
            {"Undo", QelIcon::Undo},
            {"Gavel", QelIcon::Gavel},
            {"Tachometer", QelIcon::Tachometer},
            {"CommentO", QelIcon::CommentO},
            {"CommentsO", QelIcon::CommentsO},
            {"Bolt", QelIcon::Bolt},
            {"Sitemap", QelIcon::Sitemap},
            {"Umbrella", QelIcon::Umbrella},
            {"Clipboard", QelIcon::Clipboard},
            {"LightbulbO", QelIcon::LightbulbO},
            {"Exchange", QelIcon::Exchange},
            {"CloudDownload", QelIcon::CloudDownload},
            {"CloudUpload", QelIcon::CloudUpload},
            {"UserMd", QelIcon::UserMd},
            {"Stethoscope", QelIcon::Stethoscope},
            {"Suitcase", QelIcon::Suitcase},
            {"BellO", QelIcon::BellO},
            {"Coffee", QelIcon::Coffee},
            {"Cutlery", QelIcon::Cutlery},
            {"FileTextO", QelIcon::FileTextO},
            {"BuildingO", QelIcon::BuildingO},
            {"HospitalO", QelIcon::HospitalO},
            {"Ambulance", QelIcon::Ambulance},
            {"Medkit", QelIcon::Medkit},
            {"FighterJet", QelIcon::FighterJet},
            {"Beer", QelIcon::Beer},
            {"HSquare", QelIcon::HSquare},
            {"PlusSquare", QelIcon::PlusSquare},
            {"AngleDoubleLeft", QelIcon::AngleDoubleLeft},
            {"AngleDoubleRight", QelIcon::AngleDoubleRight},
            {"AngleDoubleUp", QelIcon::AngleDoubleUp},
            {"AngleDoubleDown", QelIcon::AngleDoubleDown},
            {"AngleLeft", QelIcon::AngleLeft},
            {"AngleRight", QelIcon::AngleRight},
            {"AngleUp", QelIcon::AngleUp},
            {"AngleDown", QelIcon::AngleDown},
            {"Desktop", QelIcon::Desktop},
            {"Laptop", QelIcon::Laptop},
            {"Tablet", QelIcon::Tablet},
            {"Mobile", QelIcon::Mobile},
            {"CircleO", QelIcon::CircleO},
            {"QuoteLeft", QelIcon::QuoteLeft},
            {"QuoteRight", QelIcon::QuoteRight},
            {"Spinner", QelIcon::Spinner},
            {"Circle", QelIcon::Circle},
            {"Reply", QelIcon::Reply},
            {"GithubAlt", QelIcon::GithubAlt},
            {"FolderO", QelIcon::FolderO},
            {"FolderOpenO", QelIcon::FolderOpenO},
            {"SmileO", QelIcon::SmileO},
            {"FrownO", QelIcon::FrownO},
            {"MehO", QelIcon::MehO},
            {"Gamepad", QelIcon::Gamepad},
            {"KeyboardO", QelIcon::KeyboardO},
            {"FlagO", QelIcon::FlagO},
            {"FlagCheckered", QelIcon::FlagCheckered},
            {"Terminal", QelIcon::Terminal},
            {"Code", QelIcon::Code},
            {"ReplyAll", QelIcon::ReplyAll},
            {"StarHalfO", QelIcon::StarHalfO},
            {"LocationArrow", QelIcon::LocationArrow},
            {"Crop", QelIcon::Crop},
            {"CodeFork", QelIcon::CodeFork},
            {"ChainBroken", QelIcon::ChainBroken},
            {"Question", QelIcon::Question},
            {"Info", QelIcon::Info},
            {"Exclamation", QelIcon::Exclamation},
            {"Superscript", QelIcon::Superscript},
            {"Subscript", QelIcon::Subscript},
            {"Eraser", QelIcon::Eraser},
            {"PuzzlePiece", QelIcon::PuzzlePiece},
            {"Microphone", QelIcon::Microphone},
            {"MicrophoneSlash", QelIcon::MicrophoneSlash},
            {"Shield", QelIcon::Shield},
            {"CalendarO", QelIcon::CalendarO},
            {"FireExtinguisher", QelIcon::FireExtinguisher},
            {"Rocket", QelIcon::Rocket},
            {"Maxcdn", QelIcon::Maxcdn},
            {"ChevronCircleLeft", QelIcon::ChevronCircleLeft},
            {"ChevronCircleRight", QelIcon::ChevronCircleRight},
            {"ChevronCircleUp", QelIcon::ChevronCircleUp},
            {"ChevronCircleDown", QelIcon::ChevronCircleDown},
            {"Html5", QelIcon::Html5},
            {"Css3", QelIcon::Css3},
            {"Anchor", QelIcon::Anchor},
            {"UnlockAlt", QelIcon::UnlockAlt},
            {"Bullseye", QelIcon::Bullseye},
            {"EllipsisH", QelIcon::EllipsisH},
            {"EllipsisV", QelIcon::EllipsisV},
            {"RssSquare", QelIcon::RssSquare},
            {"PlayCircle", QelIcon::PlayCircle},
            {"Ticket", QelIcon::Ticket},
            {"MinusSquare", QelIcon::MinusSquare},
            {"MinusSquareO", QelIcon::MinusSquareO},
            {"LevelUp", QelIcon::LevelUp},
            {"LevelDown", QelIcon::LevelDown},
            {"CheckSquare", QelIcon::CheckSquare},
            {"PencilSquare", QelIcon::PencilSquare},
            {"ExternalLinkSquare", QelIcon::ExternalLinkSquare},
            {"ShareSquare", QelIcon::ShareSquare},
            {"Compass", QelIcon::Compass},
            {"CaretSquareODown", QelIcon::CaretSquareODown},
            {"CaretSquareOUp", QelIcon::CaretSquareOUp},
            {"CaretSquareORight", QelIcon::CaretSquareORight},
            {"Eur", QelIcon::Eur},
            {"Gbp", QelIcon::Gbp},
            {"Usd", QelIcon::Usd},
            {"Inr", QelIcon::Inr},
            {"Jpy", QelIcon::Jpy},
            {"Rub", QelIcon::Rub},
            {"Krw", QelIcon::Krw},
            {"Btc", QelIcon::Btc},
            {"File", QelIcon::File},
            {"FileText", QelIcon::FileText},
            {"SortAlphaAsc", QelIcon::SortAlphaAsc},
            {"SortAlphaDesc", QelIcon::SortAlphaDesc},
            {"SortAmountAsc", QelIcon::SortAmountAsc},
            {"SortAmountDesc", QelIcon::SortAmountDesc},
            {"SortNumericAsc", QelIcon::SortNumericAsc},
            {"SortNumericDesc", QelIcon::SortNumericDesc},
            {"ThumbsUp", QelIcon::ThumbsUp},
            {"ThumbsDown", QelIcon::ThumbsDown},
            {"YoutubeSquare", QelIcon::YoutubeSquare},
            {"Youtube", QelIcon::Youtube},
            {"Xing", QelIcon::Xing},
            {"XingSquare", QelIcon::XingSquare},
            {"YoutubePlay", QelIcon::YoutubePlay},
            {"Dropbox", QelIcon::Dropbox},
            {"StackOverflow", QelIcon::StackOverflow},
            {"Instagram", QelIcon::Instagram},
            {"Flickr", QelIcon::Flickr},
            {"Adn", QelIcon::Adn},
            {"Bitbucket", QelIcon::Bitbucket},
            {"BitbucketSquare", QelIcon::BitbucketSquare},
            {"Tumblr", QelIcon::Tumblr},
            {"TumblrSquare", QelIcon::TumblrSquare},
            {"LongArrowDown", QelIcon::LongArrowDown},
            {"LongArrowUp", QelIcon::LongArrowUp},
            {"LongArrowLeft", QelIcon::LongArrowLeft},
            {"LongArrowRight", QelIcon::LongArrowRight},
            {"Apple", QelIcon::Apple},
            {"Windows", QelIcon::Windows},
            {"Android", QelIcon::Android},
            {"Linux", QelIcon::Linux},
            {"Dribbble", QelIcon::Dribbble},
            {"Skype", QelIcon::Skype},
            {"Foursquare", QelIcon::Foursquare},
            {"Trello", QelIcon::Trello},
            {"Female", QelIcon::Female},
            {"Male", QelIcon::Male},
            {"Gratipay", QelIcon::Gratipay},
            {"SunO", QelIcon::SunO},
            {"MoonO", QelIcon::MoonO},
            {"Archive", QelIcon::Archive},
            {"Bug", QelIcon::Bug},
            {"Vk", QelIcon::Vk},
            {"Weibo", QelIcon::Weibo},
            {"Renren", QelIcon::Renren},
            {"Pagelines", QelIcon::Pagelines},
            {"StackExchange", QelIcon::StackExchange},
            {"ArrowCircleORight", QelIcon::ArrowCircleORight},
            {"ArrowCircleOLeft", QelIcon::ArrowCircleOLeft},
            {"CaretSquareOLeft", QelIcon::CaretSquareOLeft},
            {"DotCircleO", QelIcon::DotCircleO},
            {"Wheelchair", QelIcon::Wheelchair},
            {"VimeoSquare", QelIcon::VimeoSquare},
            {"Try", QelIcon::Try},
            {"PlusSquareO", QelIcon::PlusSquareO},
            {"SpaceShuttle", QelIcon::SpaceShuttle},
            {"Slack", QelIcon::Slack},
            {"EnvelopeSquare", QelIcon::EnvelopeSquare},
            {"Wordpress", QelIcon::Wordpress},
            {"Openid", QelIcon::Openid},
            {"Bank", QelIcon::Bank},
            {"GraduationCap", QelIcon::GraduationCap},
            {"Yahoo", QelIcon::Yahoo},
            {"Google", QelIcon::Google},
            {"Reddit", QelIcon::Reddit},
            {"RedditSquare", QelIcon::RedditSquare},
            {"StumbleuponCircle", QelIcon::StumbleuponCircle},
            {"Stumbleupon", QelIcon::Stumbleupon},
            {"Delicious", QelIcon::Delicious},
            {"Digg", QelIcon::Digg},
            {"PiedPiper", QelIcon::PiedPiper},
            {"PiedPiperAlt", QelIcon::PiedPiperAlt},
            {"Drupal", QelIcon::Drupal},
            {"Joomla", QelIcon::Joomla},
            {"Language", QelIcon::Language},
            {"Fax", QelIcon::Fax},
            {"Building", QelIcon::Building},
            {"Child", QelIcon::Child},
            {"Paw", QelIcon::Paw},
            {"Spoon", QelIcon::Spoon},
            {"Cube", QelIcon::Cube},
            {"Cubes", QelIcon::Cubes},
            {"Behance", QelIcon::Behance},
            {"BehanceSquare", QelIcon::BehanceSquare},
            {"Steam", QelIcon::Steam},
            {"SteamSquare", QelIcon::SteamSquare},
            {"Recycle", QelIcon::Recycle},
            {"Car", QelIcon::Car},
            {"Taxi", QelIcon::Taxi},
            {"Tree", QelIcon::Tree},
            {"Spotify", QelIcon::Spotify},
            {"Deviantart", QelIcon::Deviantart},
            {"Soundcloud", QelIcon::Soundcloud},
            {"Database", QelIcon::Database},
            {"FilePdfO", QelIcon::FilePdfO},
            {"FileWordO", QelIcon::FileWordO},
            {"FileExcelO", QelIcon::FileExcelO},
            {"FilePowerpointO", QelIcon::FilePowerpointO},
            {"FileImageO", QelIcon::FileImageO},
            {"FileArchiveO", QelIcon::FileArchiveO},
            {"FileAudioO", QelIcon::FileAudioO},
            {"FileMovieO", QelIcon::FileMovieO},
            {"FileCodeO", QelIcon::FileCodeO},
            {"Vine", QelIcon::Vine},
            {"Codepen", QelIcon::Codepen},
            {"JsFiddle", QelIcon::JsFiddle},
            {"LifeRing", QelIcon::LifeRing},
            {"CircleONotch", QelIcon::CircleONotch},
            {"Rebel", QelIcon::Rebel},
            {"Empire", QelIcon::Empire},
            {"GitSquare", QelIcon::GitSquare},
            {"Git", QelIcon::Git},
            {"HackerNews", QelIcon::HackerNews},
            {"TencentWeibo", QelIcon::TencentWeibo},
            {"Qq", QelIcon::Qq},
            {"Weixin", QelIcon::Weixin},
            {"PaperPlane", QelIcon::PaperPlane},
            {"PaperPlaneO", QelIcon::PaperPlaneO},
            {"History", QelIcon::History},
            {"CircleThin", QelIcon::CircleThin},
            {"Header", QelIcon::Header},
            {"Paragraph", QelIcon::Paragraph},
            {"Sliders", QelIcon::Sliders},
            {"ShareAlt", QelIcon::ShareAlt},
            {"ShareAltSquare", QelIcon::ShareAltSquare},
            {"Bomb", QelIcon::Bomb},
            {"FutbolO", QelIcon::FutbolO},
            {"Tty", QelIcon::Tty},
            {"Binoculars", QelIcon::Binoculars},
            {"Plug", QelIcon::Plug},
            {"Slideshare", QelIcon::Slideshare},
            {"Twitch", QelIcon::Twitch},
            {"Yelp", QelIcon::Yelp},
            {"NewspaperO", QelIcon::NewspaperO},
            {"Wifi", QelIcon::Wifi},
            {"Calculator", QelIcon::Calculator},
            {"Paypal", QelIcon::Paypal},
            {"GoogleWallet", QelIcon::GoogleWallet},
            {"CcVisa", QelIcon::CcVisa},
            {"CcMastercard", QelIcon::CcMastercard},
            {"CcDiscover", QelIcon::CcDiscover},
            {"CcAmex", QelIcon::CcAmex},
            {"CcPaypal", QelIcon::CcPaypal},
            {"CcStripe", QelIcon::CcStripe},
            {"BellSlash", QelIcon::BellSlash},
            {"BellSlashO", QelIcon::BellSlashO},
            {"Trash", QelIcon::Trash},
            {"Copyright", QelIcon::Copyright},
            {"At", QelIcon::At},
            {"Eyedropper", QelIcon::Eyedropper},
            {"PaintBrush", QelIcon::PaintBrush},
            {"BirthdayCake", QelIcon::BirthdayCake},
            {"AreaChart", QelIcon::AreaChart},
            {"PieChart", QelIcon::PieChart},
            {"LineChart", QelIcon::LineChart},
            {"Lastfm", QelIcon::Lastfm},
            {"LastfmSquare", QelIcon::LastfmSquare},
            {"ToggleOff", QelIcon::ToggleOff},
            {"ToggleOn", QelIcon::ToggleOn},
            {"Bicycle", QelIcon::Bicycle},
            {"Bus", QelIcon::Bus},
            {"Ioxhost", QelIcon::Ioxhost},
            {"Angellist", QelIcon::Angellist},
            {"Cc", QelIcon::Cc},
            {"Ils", QelIcon::Ils},
            {"Meanpath", QelIcon::Meanpath},
            {"Buysellads", QelIcon::Buysellads},
            {"Connectdevelop", QelIcon::Connectdevelop},
            {"Dashcube", QelIcon::Dashcube},
            {"Forumbee", QelIcon::Forumbee},
            {"Leanpub", QelIcon::Leanpub},
            {"Sellsy", QelIcon::Sellsy},
            {"Shirtsinbulk", QelIcon::Shirtsinbulk},
            {"Simplybuilt", QelIcon::Simplybuilt},
            {"Skyatlas", QelIcon::Skyatlas},
            {"CartPlus", QelIcon::CartPlus},
            {"CartArrowDown", QelIcon::CartArrowDown},
            {"Diamond", QelIcon::Diamond},
            {"Ship", QelIcon::Ship},
            {"UserSecret", QelIcon::UserSecret},
            {"Motorcycle", QelIcon::Motorcycle},
            {"StreetView", QelIcon::StreetView},
            {"Heartbeat", QelIcon::Heartbeat},
            {"Venus", QelIcon::Venus},
            {"Mars", QelIcon::Mars},
            {"Mercury", QelIcon::Mercury},
            {"Transgender", QelIcon::Transgender},
            {"TransgenderAlt", QelIcon::TransgenderAlt},
            {"VenusDouble", QelIcon::VenusDouble},
            {"MarsDouble", QelIcon::MarsDouble},
            {"VenusMars", QelIcon::VenusMars},
            {"MarsStroke", QelIcon::MarsStroke},
            {"MarsStrokeV", QelIcon::MarsStrokeV},
            {"MarsStrokeH", QelIcon::MarsStrokeH},
            {"Neuter", QelIcon::Neuter},
            {"Genderless", QelIcon::Genderless},
            {"FacebookOfficial", QelIcon::FacebookOfficial},
            {"PinterestP", QelIcon::PinterestP},
            {"Whatsapp", QelIcon::Whatsapp},
            {"Server", QelIcon::Server},
            {"UserPlus", QelIcon::UserPlus},
            {"UserTimes", QelIcon::UserTimes},
            {"Bed", QelIcon::Bed},
            {"Viacoin", QelIcon::Viacoin},
            {"Train", QelIcon::Train},
            {"Subway", QelIcon::Subway},
            {"Medium", QelIcon::Medium},
            {"YCombinator", QelIcon::YCombinator},
            {"OptinMonster", QelIcon::OptinMonster},
            {"Opencart", QelIcon::Opencart},
            {"Expeditedssl", QelIcon::Expeditedssl},
            {"BatteryFull", QelIcon::BatteryFull},
            {"BatteryThreeQuarters", QelIcon::BatteryThreeQuarters},
            {"BatteryHalf", QelIcon::BatteryHalf},
            {"BatteryQuarter", QelIcon::BatteryQuarter},
            {"BatteryEmpty", QelIcon::BatteryEmpty},
            {"MousePointer", QelIcon::MousePointer},
            {"ICursor", QelIcon::ICursor},
            {"ObjectGroup", QelIcon::ObjectGroup},
            {"ObjectUngroup", QelIcon::ObjectUngroup},
            {"StickyNote", QelIcon::StickyNote},
            {"StickyNoteO", QelIcon::StickyNoteO},
            {"CcJcb", QelIcon::CcJcb},
            {"CcDinersClub", QelIcon::CcDinersClub},
            {"Clone", QelIcon::Clone},
            {"BalanceScale", QelIcon::BalanceScale},
            {"HourglassO", QelIcon::HourglassO},
            {"HourglassStart", QelIcon::HourglassStart},
            {"HourglassHalf", QelIcon::HourglassHalf},
            {"HourglassEnd", QelIcon::HourglassEnd},
            {"Hourglass", QelIcon::Hourglass},
            {"HandRockO", QelIcon::HandRockO},
            {"HandPaperO", QelIcon::HandPaperO},
            {"HandScissorsO", QelIcon::HandScissorsO},
            {"HandLizardO", QelIcon::HandLizardO},
            {"HandSpockO", QelIcon::HandSpockO},
            {"HandPointerO", QelIcon::HandPointerO},
            {"HandPeaceO", QelIcon::HandPeaceO},
            {"Trademark", QelIcon::Trademark},
            {"Registered", QelIcon::Registered},
            {"CreativeCommons", QelIcon::CreativeCommons},
            {"Gg", QelIcon::Gg},
            {"GgCircle", QelIcon::GgCircle},
            {"Tripadvisor", QelIcon::Tripadvisor},
            {"Odnoklassniki", QelIcon::Odnoklassniki},
            {"OdnoklassnikiSquare", QelIcon::OdnoklassnikiSquare},
            {"GetPocket", QelIcon::GetPocket},
            {"WikipediaW", QelIcon::WikipediaW},
            {"Safari", QelIcon::Safari},
            {"Chrome", QelIcon::Chrome},
            {"Firefox", QelIcon::Firefox},
            {"Opera", QelIcon::Opera},
            {"InternetExplorer", QelIcon::InternetExplorer},
            {"Television", QelIcon::Television},
            {"Contao", QelIcon::Contao},
            {"FiveHundredpx", QelIcon::FiveHundredpx},
            {"Amazon", QelIcon::Amazon},
            {"CalendarPlusO", QelIcon::CalendarPlusO},
            {"CalendarMinusO", QelIcon::CalendarMinusO},
            {"CalendarTimesO", QelIcon::CalendarTimesO},
            {"CalendarCheckO", QelIcon::CalendarCheckO},
            {"Industry", QelIcon::Industry},
            {"MapPin", QelIcon::MapPin},
            {"MapSigns", QelIcon::MapSigns},
            {"MapO", QelIcon::MapO},
            {"Map", QelIcon::Map},
            {"Commenting", QelIcon::Commenting},
            {"CommentingO", QelIcon::CommentingO},
            {"Houzz", QelIcon::Houzz},
            {"Vimeo", QelIcon::Vimeo},
            {"BlackTie", QelIcon::BlackTie},
            {"Fonticons", QelIcon::Fonticons},
            {"RedditAlien", QelIcon::RedditAlien},
            {"Edge", QelIcon::Edge},
            {"CreditCardAlt", QelIcon::CreditCardAlt},
            {"Codiepie", QelIcon::Codiepie},
            {"Modx", QelIcon::Modx},
            {"FortAwesome", QelIcon::FortAwesome},
            {"Usb", QelIcon::Usb},
            {"ProductHunt", QelIcon::ProductHunt},
            {"Mixcloud", QelIcon::Mixcloud},
            {"Scribd", QelIcon::Scribd},
            {"PauseCircle", QelIcon::PauseCircle},
            {"PauseCircleO", QelIcon::PauseCircleO},
            {"StopCircle", QelIcon::StopCircle},
            {"StopCircleO", QelIcon::StopCircleO},
            {"ShoppingBag", QelIcon::ShoppingBag},
            {"ShoppingBasket", QelIcon::ShoppingBasket},
            {"Hashtag", QelIcon::Hashtag},
            {"Bluetooth", QelIcon::Bluetooth},
            {"BluetoothB", QelIcon::BluetoothB},
            {"Percent", QelIcon::Percent},
            {"Gitlab", QelIcon::Gitlab},
            {"Wpbeginner", QelIcon::Wpbeginner},
            {"Wpforms", QelIcon::Wpforms},
            {"Envira", QelIcon::Envira},
            {"UniversalAccess", QelIcon::UniversalAccess},
            {"WheelchairAlt", QelIcon::WheelchairAlt},
            {"QuestionCircleO", QelIcon::QuestionCircleO},
            {"Blind", QelIcon::Blind},
            {"AudioDescription", QelIcon::AudioDescription},
            {"VolumeControlPhone", QelIcon::VolumeControlPhone},
            {"Braille", QelIcon::Braille},
            {"AssistiveListeningSystems", QelIcon::AssistiveListeningSystems},
            {"AmericanSignLanguageInterpreting", QelIcon::AmericanSignLanguageInterpreting},
            {"Deaf", QelIcon::Deaf},
            {"Glide", QelIcon::Glide},
            {"GlideG", QelIcon::GlideG},
            {"Signing", QelIcon::Signing},
            {"LowVision", QelIcon::LowVision},
            {"Viadeo", QelIcon::Viadeo},
            {"ViadeoSquare", QelIcon::ViadeoSquare},
            {"Snapchat", QelIcon::Snapchat},
            {"SnapchatGhost", QelIcon::SnapchatGhost},
            {"SnapchatSquare", QelIcon::SnapchatSquare},
            {"FirstOrder", QelIcon::FirstOrder},
            {"Yoast", QelIcon::Yoast},
            {"Themeisle", QelIcon::Themeisle},
            {"GooglePlusOfficial", QelIcon::GooglePlusOfficial},
            {"FontAwesome", QelIcon::FontAwesome},
            {"HandshakeO", QelIcon::HandshakeO},
            {"EnvelopeOpen", QelIcon::EnvelopeOpen},
            {"EnvelopeOpenO", QelIcon::EnvelopeOpenO},
            {"Linode", QelIcon::Linode},
            {"AddressBook", QelIcon::AddressBook},
            {"AddressBookO", QelIcon::AddressBookO},
            {"AddressCard", QelIcon::AddressCard},
            {"AddressCardO", QelIcon::AddressCardO},
            {"UserCircle", QelIcon::UserCircle},
            {"UserCircleO", QelIcon::UserCircleO},
            {"UserO", QelIcon::UserO},
            {"IdBadge", QelIcon::IdBadge},
            {"IdCard", QelIcon::IdCard},
            {"IdCardO", QelIcon::IdCardO},
            {"Quora", QelIcon::Quora},
            {"FreeCodeCamp", QelIcon::FreeCodeCamp},
            {"Telegram", QelIcon::Telegram},
            {"ThermometerFull", QelIcon::ThermometerFull},
            {"ThermometerThreeQuarters", QelIcon::ThermometerThreeQuarters},
            {"ThermometerHalf", QelIcon::ThermometerHalf},
            {"ThermometerQuarter", QelIcon::ThermometerQuarter},
            {"ThermometerEmpty", QelIcon::ThermometerEmpty},
            {"Shower", QelIcon::Shower},
            {"Bath", QelIcon::Bath},
            {"Podcast", QelIcon::Podcast},
            {"WindowMaximize", QelIcon::WindowMaximize},
            {"WindowMinimize", QelIcon::WindowMinimize},
            {"WindowRestore", QelIcon::WindowRestore},
            {"WindowClose", QelIcon::WindowClose},
            {"WindowCloseO", QelIcon::WindowCloseO},
            {"Bandcamp", QelIcon::Bandcamp},
            {"Grav", QelIcon::Grav},
            {"Etsy", QelIcon::Etsy},
            {"Imdb", QelIcon::Imdb},
            {"Ravelry", QelIcon::Ravelry},
            {"Eercast", QelIcon::Eercast},
            {"Microchip", QelIcon::Microchip},
            {"SnowflakeO", QelIcon::SnowflakeO},
            {"Superpowers", QelIcon::Superpowers},
            {"Wpexplorer", QelIcon::Wpexplorer},
            {"Meetup", QelIcon::Meetup}
        };

        const int iconsCount = sizeof(icons) / sizeof(IconData);

        for (int i = 0; i < iconsCount; ++i) {
            // 创建一个 QLabel 来显示图标
            QLabel *iconLabel = new QLabel();
            iconLabel->setPixmap(QelIcon(icons[i].icon, 64).pixmap(64, 64));
            iconLabel->setAlignment(Qt::AlignCenter);
            iconLabel->setFixedSize(80, 80); // 正方形大小

                    // 创建一个 QLabel 来显示图标名称
            QLabel *nameLabel = new QLabel(icons[i].name);
            nameLabel->setAlignment(Qt::AlignCenter);

                    // 创建一个布局来包含图标和名称
            QVBoxLayout *iconLayout = new QVBoxLayout();
            iconLayout->addWidget(iconLabel, 0, Qt::AlignCenter);
            iconLayout->addWidget(nameLabel);

                    // 创建一个容器小部件来放置图标和标签
            QWidget *iconWidget = new QWidget();
            iconWidget->setLayout(iconLayout);
            iconWidget->setFixedSize(128, 128); // 正方形大小

            layout->addWidget(iconWidget, row, col);

            col++;
            if (col >= 8) { // 每行放置8个图标
                col = 0;
                row++;
            }
        }

        scrollWidget->setLayout(layout);
        scrollArea->setWidget(scrollWidget);
        mainLayout->addWidget(scrollArea);

        setLayout(mainLayout);
    }
};

#endif // QELICONTESTER_H