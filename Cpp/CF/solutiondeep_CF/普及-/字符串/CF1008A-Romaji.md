# 题目信息

# Romaji

## 题目描述

Vitya has just started learning Berlanese language. It is known that Berlanese uses the Latin alphabet. Vowel letters are "a", "o", "u", "i", and "e". Other letters are consonant.

In Berlanese, there has to be a vowel after every consonant, but there can be any letter after any vowel. The only exception is a consonant "n"; after this letter, there can be any letter (not only a vowel) or there can be no letter at all. For example, the words "harakiri", "yupie", "man", and "nbo" are Berlanese while the words "horse", "king", "my", and "nz" are not.

Help Vitya find out if a word $ s $ is Berlanese.

## 说明/提示

In the first and second samples, a vowel goes after each consonant except "n", so the word is Berlanese.

In the third sample, the consonant "c" goes after the consonant "r", and the consonant "s" stands on the end, so the word is not Berlanese.

## 样例 #1

### 输入

```
sumimasen
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
ninja
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
codeforces
```

### 输出

```
NO
```

# AI分析结果

### 题目内容（中文重写）

#### Romaji

##### 题目描述

Vitya 刚刚开始学习 Berlanese 语言。已知 Berlanese 使用拉丁字母。元音字母包括 "a", "o", "u", "i", 和 "e"。其他字母为辅音。

在 Berlanese 中，每个辅音后面必须跟着一个元音，但元音后面可以跟着任何字母。唯一的例外是辅音 "n"；在这个字母后面可以跟着任何字母（不仅限于元音），或者后面可以不跟任何字母。例如，单词 "harakiri", "yupie", "man", 和 "nbo" 是 Berlanese，而单词 "horse", "king", "my", 和 "nz" 不是。

帮助 Vitya 判断一个单词 $ s $ 是否是 Berlanese。

##### 说明/提示

在第一个和第二个样例中，除了 "n" 之外的每个辅音后面都跟着一个元音，因此这些单词是 Berlanese。

在第三个样例中，辅音 "c" 跟在辅音 "r" 后面，且辅音 "s" 位于单词末尾，因此这个单词不是 Berlanese。

##### 样例 #1

###### 输入

```
sumimasen
```

###### 输出

```
YES
```

##### 样例 #2

###### 输入

```
ninja
```

###### 输出

```
YES
```

##### 样例 #3

###### 输入

```
codeforces
```

###### 输出

```
NO
```

### 题解分析与结论

#### 题解对比

1. **封禁用户**：
   - **思路**：模拟题目要求，检查每个辅音（除了 "n"）后面是否跟着元音。
   - **难点**：处理字符串末尾的边界情况。
   - **代码**：使用 `check` 函数判断是否为元音，并在主循环中检查辅音后的字符。
   - **评分**：3星。代码简洁，但边界处理不够严谨。

2. **goodlearndaydayup**：
   - **思路**：将元音存储在数组中，逐个检查辅音后的字符是否为元音。
   - **难点**：同样需要处理字符串末尾的边界情况。
   - **代码**：使用 `pd` 函数判断是否为元音，并在主循环中检查辅音后的字符。
   - **评分**：3星。代码清晰，但边界处理仍有不足。

3. **小闸蟹**：
   - **思路**：使用 `OK` 函数判断是否为元音，逐个检查辅音后的字符是否为元音。
   - **难点**：处理字符串末尾的边界情况，并确保 "n" 后的字符不受限制。
   - **代码**：使用 `OK` 函数判断元音，并在主循环中检查辅音后的字符。
   - **评分**：4星。代码清晰，边界处理较为严谨。

#### 最优关键思路

- **核心思路**：逐个检查字符串中的每个字符，如果是辅音且不是 "n"，则检查其后的字符是否为元音。
- **边界处理**：特别注意字符串末尾的字符，避免越界访问。
- **代码实现**：使用辅助函数判断字符是否为元音，简化主逻辑。

#### 可拓展之处

- **类似题目**：可以扩展到其他语言规则的检查，如特定字母组合、特定位置字符等。
- **算法套路**：字符串遍历与条件判断是常见的基础算法，适用于多种字符串处理问题。

#### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
3. [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)

#### 个人心得摘录

- **封禁用户**：提到翻译可能有些误解，强调了辅音 "n" 的特殊性。
- **小闸蟹**：提到来自 yyf 的一句话题意，强调了辅音 "n" 的特殊性，并提供了较为严谨的边界处理。

### 所选高分题解

#### 小闸蟹 (4星)

**关键亮点**：
- 使用 `OK` 函数判断元音，代码清晰。
- 处理字符串末尾的边界情况较为严谨。
- 主逻辑简洁明了，易于理解。

**核心代码**：
```cpp
bool OK(char c) // 判断字母c是否为元音字母
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string Str;
    std::cin >> Str;

    for (std::size_t i = 0; i < Str.size(); ++i)
    {
        if (OK(Str[i])) // 如果是元音字母，则不考虑
        {
            continue;
        }
        else if (Str[i] == 'n') // 如果是辅音字母但是是'n'，则不考虑
        {
            continue;
        }
        else if (i != Str.size() - 1 && OK(Str[i + 1])) // 否则需要在辅音后面跟一个元音字母
        {
            continue;
        }
        else   // 都不符合前面的条件则说明不是Berlanese
        {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }
    std::cout << "YES" << std::endl;

    return 0;
}
```

**个人心得**：
- 强调了辅音 "n" 的特殊性，并提供了较为严谨的边界处理。

---
处理用时：36.45秒