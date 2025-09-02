# 题目信息

# Character Swap (Hard Version)

## 题目描述

This problem is different from the easy version. In this version Ujan makes at most $ 2n $ swaps. In addition, $ k \le 1000, n \le 50 $ and it is necessary to print swaps themselves. You can hack this problem if you solve it. But you can hack the previous problem only if you solve both problems.

After struggling and failing many times, Ujan decided to try to clean up his house again. He decided to get his strings in order first.

Ujan has two distinct strings $ s $ and $ t $ of length $ n $ consisting of only of lowercase English characters. He wants to make them equal. Since Ujan is lazy, he will perform the following operation at most $ 2n $ times: he takes two positions $ i $ and $ j $ ( $ 1 \le i,j \le n $ , the values $ i $ and $ j $ can be equal or different), and swaps the characters $ s_i $ and $ t_j $ .

Ujan's goal is to make the strings $ s $ and $ t $ equal. He does not need to minimize the number of performed operations: any sequence of operations of length $ 2n $ or shorter is suitable.

## 样例 #1

### 输入

```
4
5
souse
houhe
3
cat
dog
2
aa
az
3
abc
bca
```

### 输出

```
Yes
1
1 4
No
No
Yes
3
1 2
3 1
2 3
```

# AI分析结果

### 题目内容中文重写
# 字符交换（困难版本）

## 题目描述
这个问题与简单版本不同。在这个版本中，乌扬（Ujan）最多进行 $2n$ 次交换。此外，$k \le 1000$，$n \le 50$，并且需要输出具体的交换操作。如果你解决了这个问题，就可以对其发起 Hack。但只有当你同时解决了两个问题时，才能对前一个问题发起 Hack。

在多次尝试并失败后，乌扬决定再次尝试清理他的房子。他决定先整理好他的字符串。

乌扬有两个长度为 $n$ 的不同字符串 $s$ 和 $t$，它们仅由小写英文字符组成。他想让这两个字符串相等。由于乌扬很懒，他将最多进行 $2n$ 次以下操作：他选择两个位置 $i$ 和 $j$（$1 \le i,j \le n$，$i$ 和 $j$ 的值可以相等也可以不同），并交换字符 $s_i$ 和 $t_j$。

乌扬的目标是使字符串 $s$ 和 $t$ 相等。他不需要最小化操作次数：任何长度不超过 $2n$ 的操作序列都是合适的。

## 样例 #1

### 输入
```
4
5
souse
houhe
3
cat
dog
2
aa
az
3
abc
bca
```

### 输出
```
Yes
1
1 4
No
No
Yes
3
1 2
3 1
2 3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是采用贪心策略来解决字符交换问题。首先判断无解的情况，即若一个字母在两个串中的出现次数为奇数，则一定无解。然后枚举字符串的每一位，当遇到不相等的字符时，分情况讨论找到合适的交换方式，使得两个字符串逐渐相等。

各题解的思路和实现基本一致，都是通过两层循环，外层枚举当前位置，内层寻找可以用于交换的字符。对于可以替换的字符，根据其位置在 $s$ 串内还是 $t$ 串内，采取不同的交换步骤。

### 题解评分与亮点
- **dd_d（4星）**：
    - **关键亮点**：思路清晰，对无解情况和三种交换情况的讨论详细，代码注释丰富，可读性高。
- **Rex01（3星）**：
    - **关键亮点**：明确指出贪心思路，对两种情况的分析简单易懂，但代码注释较少。
- **FiraCode（3星）**：
    - **关键亮点**：通过样例直观展示两种贪心情况，但代码中部分逻辑存在小问题，如第二种情况的交换位置处理。
- **lsr1409111459（3星）**：
    - **关键亮点**：思路和代码与 Rex01 类似，有解题心得分享，提醒注意答案数组大小。

### 最优关键思路或技巧
- **无解判断**：通过统计每个字母在两个串中的出现次数，若出现次数为奇数则无解，这是一个重要的预处理步骤。
- **贪心策略**：当遇到不相等的字符时，优先寻找 $s$ 串中相同的字符进行交换；若没有，则先将 $t$ 串中的字符交换到 $s$ 串中，再进行交换。

### 拓展思路
同类型题或类似算法套路：
- 字符串匹配类问题，如给定多个字符串，通过一定的操作（如交换、替换等）使它们满足特定条件。
- 贪心策略在字符处理中的应用，如通过最少的操作使字符串满足某种规则。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心算法的经典应用，通过每次合并最小的两堆果子来求解最小代价。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心策略，按照接水时间从小到大排序，计算最小平均等待时间。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心算法，通过对线段的右端点排序，选择不重叠的线段。

### 个人心得摘录与总结
- **lsr1409111459**：贪心策略比较容易想到，但考场上因为没意识到题目难度非递增，看了眼样例就跳过了。还提醒要注意答案数组开 $2n$ 大小，否则会 WA。总结就是要认真审题，注意数组边界问题。

### 重点代码
以 dd_d 的代码为例，核心实现思想是先判断无解情况，然后枚举每一位，根据不同情况进行交换操作：
```cpp
void solve()
{
    n=read();
    memset(cnt,0,sizeof(cnt));
    scanf("%s""%s",S+1,T+1);
    for (int i=1;i<=n;i++)
        cnt[S[i]-'a']++,cnt[T[i]-'a']++;
    for (int i=0;i<26;i++)
        if (cnt[i]&1) 
        {
            puts("No");
            return;
        }
    ans.clear();
    for (int i=1;i<=n;i++)
    {
        if (S[i]==T[i]) continue;
        for (int j=i+1;j<=n;j++)
        {
            if (S[i]==S[j])
            {
                ans.push_back({j,i});
                swap(S[j],T[i]);
                break;
            }
            if (S[i]==T[j])
            {
                ans.push_back({j,j});
                swap(S[j],T[j]);
                ans.push_back({j,i});
                swap(S[j],T[i]);
                break;
            }
        }
    }
    puts("Yes");
    writeln(ans.size());
    for (auto now:ans)
        writesp(now.first),writeln(now.second);
}
```

---
处理用时：39.92秒