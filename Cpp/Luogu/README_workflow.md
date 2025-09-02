# 洛谷题目完整处理流程

## 功能概述

`luogu_complete_workflow.py` 整合了洛谷题目处理的完整流程，包括：

1. **下载新题目** - 从洛谷官方数据源下载最新题目
2. **难度分类** - 按照题目难度进行自动分类
3. **标签处理** - 按照算法标签进行题目整理
4. **题解提取** - 自动获取题目的题解内容

## 使用方法

### 完整流程（推荐）
```bash
# 执行完整流程
python cpp/luogu/luogu_complete_workflow.py

# 跳过某些步骤的完整流程
python cpp/luogu/luogu_complete_workflow.py --skip-download --skip-classify
```

### 单独执行某个步骤
```bash
# 只下载新题目
python cpp/luogu/luogu_complete_workflow.py --step 1

# 只进行难度分类
python cpp/luogu/luogu_complete_workflow.py --step 2

# 只处理标签
python cpp/luogu/luogu_complete_workflow.py --step 3

# 只提取题解
python cpp/luogu/luogu_complete_workflow.py --step 4
```

## 参数说明

- `--skip-download`: 跳过下载新题目步骤
- `--skip-classify`: 跳过难度分类步骤  
- `--skip-tags`: 跳过标签处理步骤
- `--skip-solutions`: 跳过题解提取步骤
- `--step N`: 只执行指定的步骤 (1-4)

## 前置要求

1. **配置文件**: 需要 `luogu_config.json` 文件包含cookie配置
   ```json
   {
       "cookie": "你的洛谷cookie值"
   }
   ```

2. **目录结构**: 
   ```
   cpp/luogu/
   ├── problems/           # 原始题目文件
   ├── sorted_problems/    # 按难度分类的题目
   ├── tag_problems/       # 按标签分类的题目
   ├── solution/          # 提取的题解
   └── luogu_config.json  # 配置文件
   ```

## 流程详解

### 步骤1: 下载新题目
- 从 `https://cdn.luogu.com.cn/problemset-open/latest.ndjson.gz` 下载最新题目数据
- 与现有题目对比，只保存新题目
- 新题目先保存到 `problems_YYYYMMDD` 临时文件夹
- 复制到 `problems` 目录后删除临时文件夹

### 步骤2: 难度分类
- 读取题目文件中的 `diff` 字段
- 按照难度映射表分类到对应文件夹
- 支持的难度：入门、普及-、普及、普及+、提高+、省选、NOI

### 步骤3: 标签处理
- 遍历每个难度级别的题目
- 按照130+种算法标签进行分类
- 生成 `consolidated_难度_标签.md` 和对应的题号列表文件

### 步骤4: 题解提取
- 基于标签分类结果，提取对应题目的题解
- 自动跳过已处理的题目
- 包含重试机制和频率控制，避免被限制访问

## 优势特点

1. **最小参数化**: 大部分配置都内置，只需要cookie配置
2. **流程完整**: 一个命令完成全流程
3. **增量处理**: 自动跳过已存在的文件，支持断点续传
4. **错误恢复**: 包含重试机制和临时文件清理
5. **进度显示**: 使用tqdm显示处理进度
6. **灵活执行**: 支持跳过步骤或单独执行某步骤

## 注意事项

1. 题解提取步骤需要有效的cookie配置
2. 完整流程耗时较长，建议在空闲时间运行
3. 网络请求包含延迟控制，避免触发反爬虫机制
4. 临时文件会自动清理，无需手动删除

## 输出目录说明

- `problems/`: 所有题目的原始Markdown文件
- `sorted_problems/难度/`: 按难度分类的题目文件  
- `tag_problems/难度/`: 按标签整理的题目集合
- `solution/难度/标签/`: 提取的题解文件
