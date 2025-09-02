---
title: "INDEXGEN - Index Generation"
layout: "post"
diff: 难度0
pid: SP901
tag: []
---

# INDEXGEN - Index Generation

## 题目描述

大多数非小说类书籍和参考书都有一个索引，用于帮助读者快速找到特定术语或概念。这里是一个示例：

> ```
> larch, 4, 237, 238, 414
> + Monty Python and, 64, 65, 66
> + planting of, 17
> Lenny Kravitz, 50
> + going his way, 53
> lumbago, 107
> mango
> + Chris Kattan, 380
> + storage of, 87, 90
> + use in Nethack, 500, 501
> + Vitamin C content, 192
> ```

每个索引条目由一个**主条目**组成，后面可以有零个或多个以 '+' 开头的**次级条目**。条目通常跟随有一组页码引用。然而，如果存在至少一个次级条目，主条目可能不带页码引用（例如上面的_mango_）。主条目按字母顺序排序，主条目后的次级条目也按字母顺序排列，排序时不区分大小写。页码按照升序排列，并且没有重复（同一页上的重复条目不会重复记录）。

你的任务是读取包含嵌入式索引信息的文档，并根据这些信息生成对应的索引。文档由一行或多行 ASCII 文本组成，页码从 1 开始，字符 '&' 表示新页的开始（页码加 1）。索引条目通过**标记**表示，其格式如下：

> `{_文本_%_主条目_$_次级条目_}`

其中，_文本_为索引的文本，_主条目_是可选的替代主条目，_次级条目_是可选的次级条目。'%_主条目_' 和 '$_次级条目_' 都是可选的，但如果两者都存在，必须按上述顺序出现。如果 _主条目_ 存在，则使用该条目作为主条目，否则使用 _文本_ 作为主条目。如果 _次级条目_ 存在，则该标记为其添加页码；否则，标记为主条目添加页码。单个标记不能同时为主条目和次级条目添加页码。以下是四种标记类型的示例，对应于上面示例索引的条目。

> ```
> ... his {lumbago} was acting up, so ...
> ... {Lenny%Lenny Kravitz} lit up the crowd with his version of ...
> ... Monty Python often used the {larch$Monty Python and} in ...
> ... when storing {mangos%mango$storage of}, be sure to ...
> ```

输入由一个或多个文档构成，以一个仅含 '\*\*' 的行表示输入结束。文档按顺序编号，从 1 开始。每个文档由一行或多行文本组成，通过一行仅含 '\*' 表示文档结束。文档的文本行最长79个字符（不包括换行符）。对于每个文档 _i_，输出 'DOCUMENT _i_'，随后是按照示例格式排序的索引。

请注意以下几点：

- 每个文档最多100个标记，其中最多20个主条目。
- 每个主条目最多5个次级条目。
- 每个条目最多10个唯一页码（不含重复）。
- 字符 '&' 仅用于分页，并且一个文档中最多出现500次。
- 字符 '\*' 仅用于表示文档或输入的结束。
- 标记中使用的字符 '{'、'}'、'%' 和 '$' 不会在普通文本或条目中出现。
- 标记可以跨多行。标记中的每个换行符应转为一个空格。
- 标记内的空格（包括转换后的换行符）一般保留在文本或条目中。但 '{' 后、'}' 前以及紧邻 '%' 或 '$' 的空格应忽略。
- 每个标记（包括换行符转换为空格）总长度不超过79字符。

```
输入：
Call me Ishmael.
*
One {fish $unary}, two {fish$ binary},&red {fish $ scarlet}, blue {fish$
azure}. & By { Dr. Seuss }.
*
This is a {simple } & & { document} that &{
simply %simple
$adverb
} & {illustrates %vision} &&&&& one {simple-minded% simple} {Judge}'s {vision} 
for what a {document } might { look % vision} like.
*
**

```

```
输出：
DOCUMENT 1
DOCUMENT 2
Dr. Seuss, 3
fish
+ azure, 2
+ binary, 1
+ scarlet, 2
+ unary, 1
DOCUMENT 3
document, 3, 10
Judge, 10
simple, 1, 10
+ adverb, 4
vision, 5, 10
```

 **本翻译由 AI 自动生成**

