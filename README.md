# TrafficMonitorPlugins (fork with US indices & SGE gold support)

基于 [zhongyang219/TrafficMonitorPlugins](https://github.com/zhongyang219/TrafficMonitorPlugins) **main 分支最新提交**修改的 Stock 插件定制版。

> Upstream: https://github.com/zhongyang219/TrafficMonitorPlugins (main branch)

## 修改内容（仅涉及 Stock 插件）

**在原仓库基础上修复 Stock 插件美股（如 `gb_ndx`、`gb_inx`）及黄金（`gds_AU9999`）无法正常显示的问题**，并补充金交所贵金属与全球指数解析：

| 改动 | 说明 |
|---|---|
| 修复美股 `gb_` 无法显示 | 新浪 `gb_` 系列各代码字段数不统一（`gb_ndx` 36 字段，`gb_inx` 仅 30 字段），原版按 36 字段校验导致 `gb_inx` 等被丢弃，阈值降为 30 |
| 新增 `gds_`（金交所贵金属）解析 | 如 `gds_AU9999`（沪金99.99，支付宝黄金基金标的）。实测格式与 `hf_` 类似：最新价/最高/最低/昨收/开盘在前，名称在最后一列 |
| 新增 `int_`（全球指数）解析 | 如 `int_nasdaq`（纳斯达克综合）、`int_dji`、`int_sp500` |
| 修复添加对话框 "Other" 选项 | 原版选中 Other 后保存时未保留用户输入的完整代码（如 `gds_AU9999`），导致自定义前缀丢失 |
| `TransparentWnd.cpp` 中文注释改英文 | 修复 UTF-8 无 BOM 中文注释在 GBK 代码页下的编译错误（C1075） |

## DLL 下载与使用

**下载位置**：[Release 页面](https://github.com/ryankaros/TrafficMonitorPlugins-main-withUsAndGold/releases/tag/Stock_V1.14-custom) 的 **Assets** 中下载 `Stock_x64.zip`（x64 Release 编译版，解压得到 `Stock.dll`，无需自行编译）。

**使用步骤**：

1. 从 Releases 下载 `Stock.dll`；
2. 完全退出 TrafficMonitor（右键托盘图标 → 退出）；
3. 用下载的 DLL 替换 TrafficMonitor 安装目录下 `Plugins` 文件夹中的 `Stock.dll`（建议先备份原文件）；
4. 重启 TrafficMonitor，插件管理中 Stock 插件版本应显示 1.14；
5. 添加监控项（示例）：
   - 沪深：类型选 Shangzheng/Shenzheng，代码 `000001` / `399006`
   - 美股：类型选 Meigu，代码 `ndx`（纳指100）、`inx`（标普500）
   - 黄金/全球指数：类型选 **Other**，输入完整代码 `gds_AU9999`、`int_nasdaq`

**注意**：本 DLL 为 64 位（x64），仅适用于 64 位版 TrafficMonitor。

---

## 自行编译（可选）

需 VS2019/2022 + MFC 组件：

```
msbuild TrafficMonitorPlugins.sln /t:Stock /p:Configuration=Release /p:Platform=x64
```

产物：`bin\x64\Release\Stock.dll`

## 许可

沿用上游 [MIT License](LICENSE)。
