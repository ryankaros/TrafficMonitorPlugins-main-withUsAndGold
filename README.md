# TrafficMonitorPlugins (fork with US indices & SGE gold support)

基于 [zhongyang219/TrafficMonitorPlugins](https://github.com/zhongyang219/TrafficMonitorPlugins) **main 分支最新提交**修改的 Stock 插件定制版。

> Upstream: https://github.com/zhongyang219/TrafficMonitorPlugins (main branch)

## 修改内容（仅涉及 Stock 插件）

新浪行情接口 `hq.sinajs.cn` 各数据源格式不统一，原版 Stock 插件（v1.13 发布版 / main 分支）不支持以下品种，本仓库补充了相应解析：

| 改动 | 说明 |
|---|---|
| 新增 `int_`（全球指数）解析 | 如 `int_nasdaq`（纳斯达克综合）、`int_dji`、`int_sp500` |
| 新增 `gds_`（金交所贵金属）解析 | 如 `gds_AU9999`（沪金99.99，支付宝黄金基金标的）。实测格式与 `hf_` 类似：最新价/最高/最低/昨收/开盘在前，名称在最后一列 |
| 美股字段数阈值 36→30 | 新浪 `gb_` 系列各代码字段数不统一（`gb_ndx` 36 字段，`gb_inx` 仅 30 字段），原版阈值导致 `gb_inx` 被丢弃 |
| 修复添加对话框 "Other" 选项 | 原版选中 Other 后保存时未保留用户输入的完整代码（如 `gds_AU9999`），导致自定义前缀丢失 |
| `TransparentWnd.cpp` 中文注释改英文 | 修复 UTF-8 无 BOM 中文注释在 GBK 代码页下的编译错误（C1075） |

## 使用

1. 编译（需 VS2019/2022 + MFC）：
   ```
   msbuild TrafficMonitorPlugins.sln /t:Stock /p:Configuration=Release /p:Platform=x64
   ```
   产物：`bin\x64\Release\Stock.dll`
2. 退出 TrafficMonitor，用新 DLL 替换其 `Plugins` 目录下的 `Stock.dll`，重启；
3. 添加监控项（示例）：
   - 沪深：类型选 Shangzheng/Shenzheng，代码 `000001` / `399006`
   - 美股：类型选 Meigu，代码 `ndx`（纳指100）、`inx`（标普500）
   - 黄金/全球指数：类型选 **Other**，输入完整代码 `gds_AU9999`、`int_nasdaq`

## 许可

沿用上游 [MIT License](LICENSE)。
