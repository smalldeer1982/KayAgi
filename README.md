
# 三个文件的区别分析

## 1. `luogu_parser.py`
- **主要功能**：爬取洛谷网站已分类题目的详细信息和题解
- **数据源**：从`tag_problems`目录下提取的题目ID列表
- **目录结构**：按难度和分类创建目录（如`solution/普及+/分块`）
- **Cookie配置**：使用用户`1250118`的凭据
- **处理流程**：提取题目ID → 爬取题目和题解 → 转换为Markdown

## 2. `luogu_parser_tag.py`
- **主要功能**：处理标签(tag)相关的爬取工作，更复杂和全面
- **功能特点**：
  - 提供标签ID到中文名称的映射表
  - 可直接从网站获取标签信息
  - 支持按标签ID爬取题目列表
  - 包含多种标签提取方法
- **额外功能**：
  - 支持调试（保存HTML和JSON响应）
  - 提供目录结构检查
  - 可从现有题目文件中提取标签信息
- **文件长度**：代码量明显多于其他两个文件

## 3. `luogu_parser_notag.py`
- **主要功能**：爬取未分类题目的详细信息和题解
- **数据源**：从`notag_problems`目录提取的题目ID列表
- **目录结构**：与luogu_parser.py类似，但处理无标签题目
- **Cookie配置**：使用用户`1677231`的凭据
- **其他特点**：与`luogu_parser.py`基础功能相似，但专注于无标签题目

## 总结
这三个文件是针对不同场景的爬虫工具：
- `luogu_parser.py`：处理已分类题目
- `luogu_parser_tag.py`：专注标签系统和标签映射
- `luogu_parser_notag.py`：处理未分类题目


##git
git add .
git commit -m "0429更新"
git push -u origin master