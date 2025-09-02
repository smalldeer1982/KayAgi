# Skibidus and Amog'u

## 题目描述

Skibidus 降落到一颗陌生的星球，当地的 Amog 部落讲着 Amog'u 语言。在 Amog'u 语言中，名词有两种形式：单数和复数。

设名词的词根为 $ S $，则这两种形式分别转写为：

- **单数形式**：$ S $ $ + $ "us"
- **复数形式**：$ S $ $ + $ "i"

其中，$ + $ 表示 [字符串拼接](https://zh.wikipedia.org/wiki/%E4%B8%B2%E6%8E%A5)。例如，abc $ + $ def $ = $ abcdef。

例如，当 $ S $ 被转写为 "amog" 时，单数形式为 "amogus"，复数形式为 "amogi"。请注意，Amog'u 语言中的名词可以具有空的词根 —— 具体来说，"us" 是空词根对应的单数形式，而 "i" 则是复数形式（顺便提一句，这两个词分别意为 “imposter”（冒充者）和 “imposters”（冒充者们））。

给定一个转写为单数形式的 Amog'u 名词，请将其转换为相应复数形式的转写。

## 样例 #1

### 输入

```
9
us
sus
fungus
cactus
sussus
amogus
chungus
ntarsus
skibidus```

### 输出

```
i
si
fungi
cacti
sussi
amogi
chungi
ntarsi
skibidi```

