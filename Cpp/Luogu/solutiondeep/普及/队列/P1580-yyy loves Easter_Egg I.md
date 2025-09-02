# 题目信息

# yyy loves Easter_Egg I

## 题目背景

Soha 的出题效率着实让人大吃一惊。OI，数学，化学的题目都出好了，物理的题还没有一道。于是，Huntfire，absi2011，redbag 对 soha 进行轮番炸，准备炸到 soha 出来，不料，人群中冲出了个 kkksc03……

## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1456.png)

![](https://cdn.luogu.com.cn/upload/pic/1455.png)

yyy loves OI（Huntfire），yyy loves Maths（redbag），yyy loves Chemistry（absi2011）对 yyy loves Physics（soha）进行轮番炸，轰炸按照顺序进行，顺序为 Huntfire，redbag，absi2011。

现在这一题中，我们不考虑太复杂的队形形式。我们认为只要这一句内含有且恰好含有一次@，@的人和上一句话一样就算为队形。

比如以下也视为队形：

- `yyy loves OI : @yyy loves Microelectronic`
- `yyy loves Maths : @yyy loves Microelectronic 我佩服soha的出题效率`
- `yyy loves OI : @yyy loves Microelectronic +1`
- `yyy loves Chemistry : +1 @yyy loves Microelectronic`

若 @ 的人与第一个人不同，就算队形被打破。若这个人在队形被打破之前出来发言了，或者就是他打破队形了，就算（油）炸成功了。

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏先输出 `Unsuccessful @某某某 attempt`，再输出队形第一次被破坏的行数与第一次破坏队形的人的 $\text{id}$。

如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。

~~p.s.yyy loves Microelectronic 是 kkksc03~~



## 说明/提示

**@yyy loves Physics 我佩服你的出题效率**

此题仅吐槽 soha，纪念出题者的队形，此队形长达 $91$ 行。

对于 $100\%$ 的数据,每行消息长度 $\le$ $10^3$。 

- 保证行数不超过 $5\times 10^4$；
- 保证输入文件大小不超过 $4\text{MB}$；
- 保证第一个说话的一定在 @ 某人；
- 保证大家的名字都是 $\text{yyy loves ***}$ 的格式；
- 保证每个人说的话中没有 `:`；
- 保证第一个说话的一定艾特了一个人且只 @ 了一个人；
- 保证第一个说话的一定不会艾特自己；
- 保证文件结束一定有一行空行，方便你判定文件结束；
- 并不保证后面说话的艾特了几个人 然而艾特人数不为一个人视为破坏队形；
- 并不保证后面说话是否会反复艾特同一个人；
- 并不保证被炸的人一定破坏队形；
- 并不保证这一题是或不是压轴题；
- 并不保证这一套比赛存在压轴题；
- 并不保证下一套比赛和这一套比赛一样水；
- 并不保证群里除了这 $4$ 个人和 kkksc03 以外没有别人了；
- 并不保证你没 AC 这题的情况下吐槽 soha 不会出事儿；
- AC 了可以吐槽 soha 一句，soha 不会介意。

## 样例 #1

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Microelectronic : ni men wu liao me 
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv

```

### 输出

```
Unsuccessful @yyy loves Physics attempt
4
yyy loves Microelectronic
```

## 样例 #2

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Physics : ni men gou le 

```

### 输出

```
Successful @yyy loves Physics attempt
```

# AI分析结果

### 综合分析与结论

本题的核心在于字符串处理和模拟，主要难点在于如何准确提取发言者和被@的人名，并判断队形是否被破坏或轰炸是否成功。题解中，大部分作者都采用了字符串分割、查找和比较的方法，但实现方式和细节处理有所不同。以下是对题解的总结与对比：

1. **思路清晰度**：部分题解（如ironwheel、Deny_小田）通过多个函数模块化处理，逻辑清晰，易于理解；而另一些题解（如Wen_kr、AFOier）则直接在主函数中处理，代码较为紧凑但可读性稍差。
  
2. **代码可读性**：使用`string`类和`getline`的题解（如ironwheel、Deny_小田）代码更简洁，而使用`char`数组和`gets`的题解（如クリオネ、HanPi）则略显复杂，且容易因换行符处理不当导致错误。

3. **优化程度**：部分题解（如ironwheel、Deny_小田）通过提前判断和处理换行符，减少了不必要的错误；而另一些题解（如Wen_kr、AFOier）则直接在循环中处理，代码较为冗长。

### 所选高星题解

#### 1. 题解作者：ironwheel（5星）
**关键亮点**：
- 通过多个函数模块化处理，逻辑清晰，代码可读性强。
- 使用`getline`和`string`类，避免了`char`数组的复杂性。
- 提前处理换行符，减少了错误。

**个人心得**：
- 作者提到在处理换行符时遇到问题，通过特判解决了WA问题。

**核心代码**：
```cpp
string search(string s, int l) {
    string kk;
    int spacesum = 0;
    for (register int i = l; s[i] != ' ' && i < s.size(); i++) {
        if (s[i] == ' ') spacesum++;
        if (spacesum == 3 || s[i] == 13) break;
        kk += s[i];
    }
    return kk;
}
```

#### 2. 题解作者：Deny_小田（4.5星）
**关键亮点**：
- 使用`sscanf`和`strstr`函数简化了字符串处理，代码简洁。
- 通过`count`函数判断@的个数，减少了代码复杂度。
- 提前处理换行符，避免了不必要的错误。

**核心代码**：
```cpp
sscanf(strstr(s, "@"), "@yyy loves %s", name);
while (c++) {
    gets(s);
    int len = strlen(s);
    if (len == 1) break;
    sscanf(s, "yyy loves %s", importer);
    if (!strcmp(importer, name)) {
        printf("Successful @yyy loves %s attempt\n", name);
        return 0;
    }
    if (count(s, s + len, '@') != 1 || (sscanf(strstr(s, "@"), "@yyy loves %s", t), strcmp(t, name))) {
        printf("Unsuccessful @yyy loves %s attempt\n", name);
        printf("%d\n", c);
        printf("yyy loves %s\n", importer);
        return 0;
    }
}
```

#### 3. 题解作者：HanPi（4星）
**关键亮点**：
- 使用`scanf`格式化输入，简化了字符串处理。
- 通过`GetAtName`函数提取被@的人名，代码结构清晰。
- 提前处理换行符，减少了错误。

**核心代码**：
```cpp
int GetAtName(const char str[], char dest[]) {
    int i = 0, j = 0, flag = 1;
    while (str[i]) {
        if (str[i] == '@') {
            flag = 0;
            break;
        }
        i++;
    }
    if (flag) return 0;
    i += 11;
    while (str[i] && str[i] != ' ' && str[i] != '\r') {
        dest[j++] = str[i++];
    }
    dest[j] = 0;
    return 1;
}
```

### 最优关键思路与技巧

1. **模块化处理**：将字符串处理、人名提取、队形判断等功能模块化，提高代码的可读性和可维护性。
2. **提前处理换行符**：通过提前判断和处理换行符，减少因换行符导致的错误。
3. **使用`sscanf`和`strstr`**：这些函数可以简化字符串的提取和比较，减少代码复杂度。

### 可拓展之处

- **同类型题**：类似的字符串处理和模拟题可以通过模块化处理和提前判断换行符来提高代码的鲁棒性。
- **算法套路**：在处理字符串时，可以使用`sscanf`、`strstr`等函数简化处理流程。

### 推荐题目

1. **P1305 新二叉树**（字符串处理与树结构）
2. **P1553 数字反转（升级版）**（字符串处理与模拟）
3. **P1598 垂直柱状图**（字符串处理与统计）

### 个人心得总结

- **调试经历**：多位作者提到在处理换行符时遇到问题，通过特判或提前处理解决了WA问题。
- **踩坑教训**：使用`char`数组和`gets`时，容易因换行符处理不当导致错误，建议使用`string`类和`getline`。
- **顿悟感想**：模块化处理和提前判断换行符可以显著提高代码的鲁棒性和可读性。

---
处理用时：44.06秒