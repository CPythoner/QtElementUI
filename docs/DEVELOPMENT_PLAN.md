# QtElementUI 开发计划（Roadmap）

## 1. 当前仓库现状（基线）

### 1.1 已有组件与工程结构
- 当前顶层工程通过 `subdirs` 方式组织，已纳入四个子工程：`QelIcon`、`QelButton`、`QelNumberInput`、`QelShow`。
- `QelShow` 作为组件展示工程，当前已注册并可切换上述 3 个组件的测试页面。
- README 中已经明确了项目目标（在 Qt 中实现 Element 风格组件）以及现阶段示例范围（Icon/Button/NumberInput）。

### 1.2 现阶段能力判断
当前项目已经具备“组件雏形 + 展示入口 + 按需引入（.pri）”的基础，但距离“覆盖 ElementUI 全量组件”还缺以下关键能力：
1. **统一设计令牌（Design Tokens）层**：颜色、字号、间距、圆角、阴影、状态色尚未形成可复用规范。
2. **通用基础能力层**：主题切换（浅色/深色）、状态机、动画、弹层定位、表单校验、国际化、可访问性（键盘/焦点）等尚未抽象。
3. **组件覆盖率不足**：目前主要是基础输入与按钮，缺少导航、反馈、数据展示、复杂容器等大类组件。
4. **工程质量体系不足**：自动化测试、截图回归、CI 构建矩阵、版本发布规范尚未体系化。

---

## 2. 总体目标与验收口径

### 2.1 总体目标
在 Qt Widgets 体系中，分阶段实现与 ElementUI/Element Plus 对齐的组件库，保证：
- API 风格统一、易于迁移；
- 视觉与交互行为尽量贴近 Element；
- 具备工程可维护性（测试、文档、示例、版本化发布）。

### 2.2 验收口径（每个组件都应满足）
- **功能**：核心 props/状态/事件齐全（至少覆盖常见 80% 场景）。
- **视觉**：默认态、hover、active、disabled 与 Element 设计基线一致。
- **交互**：键盘可用（Tab/Enter/Esc/方向键等），焦点表现明确。
- **文档**：示例 + API 表格 + 常见问题。
- **测试**：单元测试 + 至少 1 个展示页可回归截图。

---

## 3. 分阶段开发路线（建议 4 个阶段）

## Phase 0（2 周）：基础设施补齐
目标：为后续大量组件开发建立“可复用地基”。

### 关键任务
1. **设计令牌层**
   - 新建 `QelTheme` 或 `QelDesignTokens` 模块，统一管理颜色、字体、间距、圆角、阴影、z-index。
   - 从当前 Button 色值中抽离硬编码，统一由 token 获取。
2. **基础工具层**
   - 增加工具类：`QelStyleHelper`、`QelAnimationHelper`、`QelPopupManager`。
   - 定义组件状态模型（normal/hover/active/focus/disabled/loading）。
3. **工程规范与质量门禁**
   - 增加基础单元测试工程（建议 `Qt Test`）。
   - 增加静态检查与格式化规则（如 clang-format）。
   - 建立最小 CI：可编译 + 测试通过。

### 里程碑产出
- 主题 token 可在 `QelButton` 与 `QelNumberInput` 落地替换。
- 新增 `docs/` 规范文档：命名、状态、事件、样式约定。

---

## Phase 1（4~6 周）：高频基础组件补全
目标：先覆盖业务最常用控件，形成“可用套件”。

### 组件优先级（建议）
1. `QelInput`（text/password/clearable/show-password）
2. `QelSelect`（单选，后续扩展多选/远程搜索）
3. `QelCheckbox` / `QelRadio` / `QelSwitch`
4. `QelForm` + `QelFormItem`（基础校验联动）
5. `QelTag` / `QelBadge` / `QelProgress`

### 关键策略
- 统一 API 命名：贴近 Element（如 `size`、`disabled`、`clearable`、`placeholder`）。
- 每个组件上线时同时补齐：
  - `*.h/*.cpp/*.pri`
  - `Tester` 展示页
  - README 文档片段
  - 基础测试用例

### 里程碑产出
- `QelShow` 可展示 8~10 个组件。
- 表单场景（输入、选择、校验、提交）可跑通。

---

## Phase 2（6~8 周）：导航与反馈体系
目标：完善中后台界面的结构与反馈能力。

### 组件优先级（建议）
1. 导航：`QelMenu`、`QelTabs`、`QelBreadcrumb`、`QelPagination`
2. 反馈：`QelDialog`、`QelDrawer`、`QelMessage`、`QelMessageBox`、`QelNotification`
3. 数据展示：`QelTable`（基础版）、`QelTooltip`、`QelPopover`

### 技术重点
- 弹层定位与层级管理（避免遮挡、窗口边界裁剪）。
- 焦点陷阱（Dialog/Drawer）与 Esc 关闭等键盘交互。
- `QelTable` 先实现基础功能：列定义、斑马纹、固定表头、空状态。

### 里程碑产出
- 具备“列表页 + 编辑弹窗 + 全局消息提示”的完整业务流。

---

## Phase 3（8~12 周）：复杂组件与发布体系
目标：冲刺“ElementUI 级别组件库”可发布版本。

### 组件优先级（建议）
1. 复杂输入：`QelDatePicker`、`QelTimePicker`、`QelCascader`、`QelTreeSelect`
2. 复杂数据：`QelTree`、`QelTable` 增强（排序/筛选/分页/自定义渲染）
3. 上传与媒体：`QelUpload`
4. 高级容器：`QelCollapse`、`QelCard`、`QelTimeline`

### 发布与生态
- 版本化策略（SemVer）。
- CHANGELOG 与迁移文档。
- Demo 打包发布（可执行展示程序 + 截图文档）。
- 提供最小业务模板工程（可直接集成）。

### 里程碑产出
- 发布 `v1.0.0-beta`：覆盖核心中后台页面 70% 以上 UI 需求。

---

## 4. 组件优先级总表（按业务价值）

### P0（必须优先）
- Input / Select / Checkbox / Radio / Switch / Form / Dialog / Message / Table(基础)

### P1（高优先）
- Tabs / Menu / Pagination / Tooltip / Popover / Drawer / Notification / Tag / Badge

### P2（增强）
- DatePicker / TimePicker / Cascader / Tree / Upload / Timeline / Skeleton / Empty

---

## 5. 协作方式与节奏建议

- 建议采用 **“每周一个小迭代”**：
  - 周初定义本周 1~2 个组件目标；
  - 周中完成开发与联调；
  - 周末交付示例、文档、测试。
- 每个组件通过统一模板立项（需求清单、状态图、API 草案、完成定义 DoD）。
- 每两周做一次样式一致性审查（跨组件对齐边距、字号、交互反馈时长）。

---

## 6. 下一步（可立即执行）

1. 建立 `QelTheme`（token）并先接入 `QelButton`。
2. 新建 `QelInput` 组件（作为后续 Form 的基础）。
3. 在 `QelShow` 中增加分类导航（基础组件 / 表单组件 / 反馈组件 / 数据组件）。
4. 新增最小 Qt Test 工程，先覆盖 `QelButton` 与 `QelNumberInput` 的基础行为。

> 完成以上 4 项后，仓库将从“演示型项目”进入“可持续扩展的组件库项目”。
