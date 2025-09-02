# 题目信息

# Azamon Web Services

## 题目描述

Your friend Jeff Zebos has been trying to run his new online company, but it's not going very well. He's not getting a lot of sales on his website which he decided to call Azamon. His big problem, you think, is that he's not ranking high enough on the search engines. If only he could rename his products to have better names than his competitors, then he'll be at the top of the search results and will be a millionaire.

After doing some research, you find out that search engines only sort their results lexicographically. If your friend could rename his products to lexicographically smaller strings than his competitor's, then he'll be at the top of the rankings!

To make your strategy less obvious to his competitors, you decide to swap no more than two letters of the product names.

Please help Jeff to find improved names for his products that are lexicographically smaller than his competitor's!

Given the string $ s $ representing Jeff's product name and the string $ c $ representing his competitor's product name, find a way to swap at most one pair of characters in $ s $ (that is, find two distinct indices $ i $ and $ j $ and swap $ s_i $ and $ s_j $ ) such that the resulting new name becomes strictly lexicographically smaller than $ c $ , or determine that it is impossible.

Note: String $ a $ is strictly lexicographically smaller than string $ b $ if and only if one of the following holds:

- $ a $ is a proper prefix of $ b $ , that is, $ a $ is a prefix of $ b $ such that $ a \neq b $ ;
- There exists an integer $ 1 \le i \le \min{(|a|, |b|)} $ such that $ a_i < b_i $ and $ a_j = b_j $ for $ 1 \le j < i $ .

## 说明/提示

In the first test case, it is possible to swap the second and the fourth letters of the string and the resulting string "AMAZON" is lexicographically smaller than "APPLE".

It is impossible to improve the product's name in the second test case and satisfy all conditions.

In the third test case, it is possible not to swap a pair of characters. The name "APPLE" is lexicographically smaller than "BANANA". Note that there are other valid answers, e.g., "APPEL".

## 样例 #1

### 输入

```
3
AZAMON APPLE
AZAMON AAAAAAAAAAALIBABA
APPLE BANANA
```

### 输出

```
AMAZON
---
APPLE
```

# AI分析结果

### 题目内容中文重写
# Azamon网络服务

## 题目描述
你的朋友杰夫·泽博斯（Jeff Zebos）一直在努力经营他的新在线公司，但进展不太顺利。他的网站（他决定命名为Azamon）销量不佳。你认为他的大问题是在搜索引擎上的排名不够高。要是他能给产品重命名，使其名称比竞争对手的更靠前，那他就能在搜索结果中名列前茅，成为百万富翁。

经过一番研究，你发现搜索引擎只按字典序对结果进行排序。如果你的朋友能将产品重命名为字典序比竞争对手小的字符串，那他就能在排名中名列前茅！

为了不让竞争对手轻易察觉你的策略，你决定最多交换产品名称中的两个字母。

请帮助杰夫为他的产品找到改进后的名称，使其字典序小于竞争对手的名称！

给定代表杰夫产品名称的字符串 $s$ 和代表他竞争对手产品名称的字符串 $c$，找到一种方法，最多交换 $s$ 中的一对字符（即找到两个不同的索引 $i$ 和 $j$，交换 $s_i$ 和 $s_j$），使得到的新名称在字典序上严格小于 $c$，或者确定这是不可能的。

注意：字符串 $a$ 在字典序上严格小于字符串 $b$ 当且仅当以下条件之一成立：
- $a$ 是 $b$ 的真前缀，即 $a$ 是 $b$ 的前缀且 $a \neq b$；
- 存在一个整数 $1 \le i \le \min(|a|, |b|)$，使得 $a_i < b_i$ 且对于 $1 \le j < i$ 有 $a_j = b_j$。

## 说明/提示
在第一个测试用例中，可以交换字符串的第二个和第四个字母，得到的字符串 “AMAZON” 在字典序上小于 “APPLE”。
在第二个测试用例中，不可能改进产品名称并满足所有条件。
在第三个测试用例中，可以不交换一对字符。名称 “APPLE” 在字典序上小于 “BANANA”。注意还有其他有效的答案，例如 “APPEL”。

## 样例 #1
### 输入
```
3
AZAMON APPLE
AZAMON AAAAAAAAAAALIBABA
APPLE BANANA
```
### 输出
```
AMAZON
---
APPLE
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过最多一次交换操作，让字符串 $s$ 的字典序小于字符串 $c$。大部分题解采用贪心策略，尝试找到能使 $s$ 字典序最小的交换方式。
- **思路对比**：多数题解是枚举 $s$ 的每个位置，找到合适的字符进行交换；部分题解使用数据结构（如堆、集合）来优化查找最小字符的过程。
- **算法要点**：主要是通过贪心思想，让字典序小的字符尽量靠前，同时考虑交换位置的选择，使得到的字符串字典序最小。
- **解决难点**：要处理好字符重复的情况，避免有解被当成无解；还要注意交换后字符串的字典序比较。

### 所选题解
- **万弘的题解（5星）**：
    - **关键亮点**：思路清晰，代码简洁，直接枚举每个位置，用后面最小的字符进行交换，若满足条件则输出，否则继续尝试。
    - **个人心得**：作者提到第一眼看错贪心策略，吃了两口罚时，提醒我们做题时要仔细思考贪心的正确性。
- **ccxswl的题解（4星）**：
    - **关键亮点**：在多数 $O(n^2)$ 复杂度题解的基础上，提出了 $O(n\log n)$ 复杂度的解法，使用堆和集合优化查找最小字符的过程。
    - **个人心得**：通过具体样例指出了初始代码的错误，强调了在贪心时要让字典序大的字母越靠后越优。
- **copper_ingot的题解（4星）**：
    - **关键亮点**：详细解释了暴力枚举的思路，并进行了优化，通过特判和找最小且最靠后的字符进行交换，降低了时间复杂度。

### 重点代码
#### 万弘的题解
```cpp
str a,b;
void work()
{
    std::cin>>a>>b;
    for(ll s=0;s<a.size();++s)
    {
        ll pos=s;
        for(ll i=s+1;i<a.size();++i)
            if(a[i]<=a[pos])pos=i;
        std::swap(a[s],a[pos]);
        if(a<b)
        {
            std::cout<<a<<std::endl;
            return;
        }
        std::swap(a[s],a[pos]);
    }
    std::cout<<"---"<<std::endl;
}
int main()
{
    ll task=read();
    while(task--)work();
    return 0;
}
```
**核心实现思想**：枚举字符串 $a$ 的每个位置，找到该位置后面最小的字符，交换后判断是否满足条件，若不满足则恢复交换。

#### ccxswl的题解
```cpp
set<pii> p;
void Sol() {
    p.clear();
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < s.size(); i++)
        p.insert({s[i], i});
    for (auto &i : s) {
        char mn = (*p.begin()).first;
        if (i == mn) p.erase(p.begin());
        else {
            auto it = --p.lower_bound({mn, int(1e9)});
            swap(i, s[(*it).second]);
            break;
        }
    }
    if (s < t) cout << s << '\n';
    else puts("---");
}
```
**核心实现思想**：使用集合存储字符及其位置，从前往后遍历字符串，若当前字符不是最小字符，则找到最小且最靠后的字符进行交换。

#### copper_ingot的题解
```cpp
bool sless(){
    for (int i = 0; i < min(n, m); i++){
        if (s[i] < c[i]) return true;
        else if (s[i] > c[i]) return false;
    }
    if (n < m) return true;
    else return false;
}
signed main(){
    scanf("%d", &t);
    while (t--){
        scanf("%s%s", s, c);
        n = strlen(s), m = strlen(c);
        if (sless()){printf("%s\n", s); continue;}//特判
        int flag = 0;
        for (int i = 0; i < n; i++){
            char minc = char('Z' + 1);
            int pos = 0;
            for (int j = i + 1; j < n; j++)
                if (s[j] <= minc) minc = s[j], pos = j;//往后找最小的
            swap(s[i], s[pos]);
            if (sless()){printf("%s\n", s); flag = 1; break;}
            swap(s[i], s[pos]);
        }
        if (!flag) puts("---");//记得无解
    }
    return 0;
}
```
**核心实现思想**：先特判 $s$ 是否本来就小于 $c$，然后枚举 $s$ 的每个位置，找到该位置后面最小且最靠后的字符进行交换，判断是否满足条件。

### 扩展思路
同类型题可能会有更多限制条件，如交换次数限制、对交换位置的限制等。类似算法套路可以应用在其他字符串处理问题中，通过贪心策略优化字符串的排列。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：贪心算法的经典应用，通过优先队列优化。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心策略，按照接水时间从小到大排序。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心算法，按照结束时间排序。

### 个人心得总结
- 万弘：做题时要仔细思考贪心的正确性，避免看错策略导致罚时。
- ccxswl：在贪心时要考虑全面，通过具体样例检查代码的正确性，注意让字典序大的字母越靠后越优。

---
处理用时：58.04秒