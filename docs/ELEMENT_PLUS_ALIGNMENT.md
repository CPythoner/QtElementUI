# Element Plus Alignment Policy

QtElementUI uses **Element Plus current stable** as the single reference baseline for component behavior, defaults, API semantics, interaction, and visual design.

Current pinned baseline: **Element Plus 2.14.6**.

## 1. Source of truth

Before implementing or refactoring a component:

1. Check the current stable Element Plus documentation.
2. Check the corresponding Element Plus source code when behavior or defaults are ambiguous.
3. Record the referenced Element Plus version in the pull request.
4. Prefer current stable behavior over legacy Element UI 2.x behavior.

Element UI 2.x may only be used as historical compatibility context.

## 2. Alignment rules

Map Element Plus concepts to Qt-native concepts rather than copying Web APIs mechanically.

| Element Plus concept | QtElementUI mapping |
| --- | --- |
| props / defaults | setter/getter, constructor option, enum, value type |
| emits / events | Qt signals |
| v-model / controlled state | property + setter/getter + change signal |
| slots | QWidget content, delegate, renderer, callback |
| CSS variables | QelTheme tokens |
| CSS state composition | QelStyleHelper |
| transition | QelAnimationHelper |
| Popper positioning | QelPopupManager |
| teleport / append-to | Qt popup/top-level widget parenting |
| virtual reference | QWidget or geometry-based target abstraction |
| keyboard / focus behavior | Qt focus policy and event handling |

Do not expose no-op C++ APIs only to match a Web prop name.

## 3. Component PR checklist

Every new component or substantial component refactor should document:

- Element Plus version used as reference;
- API and default-value comparison;
- states: normal / hover / active / focus / disabled / loading where applicable;
- signals/events mapping;
- keyboard and focus behavior;
- Theme/StyleHelper usage;
- popup/animation mapping where applicable;
- QelShow examples covering important variants;
- Web-only APIs intentionally omitted or mapped differently.

## 4. Existing components

The following existing components should be audited incrementally against the current Element Plus API when they are next modified:

- QelButton
- QelInput
- QelNumberInput
- QelSelect
- QelCheckbox
- QelRadio
- QelSwitch
- QelForm / QelFormItem
- QelTooltip

Do not perform compatibility churn only for naming. Prioritize behavioral/default-value gaps and missing high-value APIs.

## 5. New components

All new components start directly from the current Element Plus API.

Recommended next sequence:

1. QelTag
2. QelBadge
3. QelProgress
4. QelDialog
5. QelMessage
6. QelTable

For each component, inspect Element Plus first, then design the Qt-native API.
