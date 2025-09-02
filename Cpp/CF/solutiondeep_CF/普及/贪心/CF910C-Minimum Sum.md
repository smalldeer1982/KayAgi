# 题目信息

# Minimum Sum

## 题目描述

Petya 有一个长度为n的正整数序列 $a_{1},a_{2},...,a_{n}$。他的朋友Vasya 想要捉弄他，Vasya用一个字母替换了Petya 的号码中的所有数字。

他用小写字母‘a’到‘j’中的一个字母替换了所有数字 0，用另一个字母替换了所有 1，依次类推。对于不同的两个数字，Vasya 用‘a’到‘j’中不同的字母。

你的任务是还原 Petya 的序列。还原得到的数字应是没有前导零（数字开头没有零）的正整数。由于可能有多种方式实现，所以要求恢复后的序列总和最小。保证初始时序列中数字没有前导零。

## 样例 #1

### 输入

```
3
ab
de
aj
```

### 输出

```
47
```

## 样例 #2

### 输入

```
5
abcdef
ghij
bdef
accbd
g
```

### 输出

```
136542
```

## 样例 #3

### 输入

```
3
aa
jj
aa
```

### 输出

```
44
```

# AI分析结果

【题目内容】
# Minimum Sum

## 题目描述

Petya 有一个长度为n的正整数序列 $a_{1},a_{2},...,a_{n}$。他的朋友Vasya 想要捉弄他，Vasya用一个字母替换了Petya 的号码中的所有数字。

他用小写字母‘a’到‘j’中的一个字母替换了所有数字 0，用另一个字母替换了所有 1，依次类推。对于不同的两个数字，Vasya 用‘a’到‘j’中不同的字母。

你的任务是还原 Petya 的序列。还原得到的数字应是没有前导零（数字开头没有零）的正整数。由于可能有多种方式实现，所以要求恢复后的序列总和最小。保证初始时序列中数字没有前导零。

## 样例 #1

### 输入

```
3
ab
de
aj
```

### 输出

```
47
```

## 样例 #2

### 输入

```
5
abcdef
ghij
bdef
accbd
g
```

### 输出

```
136542
```

## 样例 #3

### 输入

```
3
aa
jj
aa
```

### 输出

```
44
```

【题解分析与结论】

各题解的思路基本一致，核心思想是通过计算每个字母的权重（即该字母在所有字符串中的位置对应的10的幂次和），然后根据权重从大到小排序，优先为权重大的字母分配较小的数字，以确保最终的和最小。需要注意的是，某些字母不能为0（即作为字符串的首字母），因此需要特别处理。

【评分较高的题解】

1. **作者：chengni (4星)**
   - **关键亮点**：思路清晰，代码简洁，直接通过结构体存储字母的权重和是否为首字母，排序后优先为权重大的字母分配较小的数字，特别处理不能为0的情况。
   - **代码核心**：
     ```cpp
     struct node {
         int a,b;
     }t[100000];
     bool cmp(node x,node y){
         return x.a>y.a;
     }
     int main(){
         int n=read();
         for(int i=1;i<=n;i++){
             cin>>c;
             int l=strlen(c);
             for(int j=0;j<l;j++){
                 t[c[j]-'a'+1].a+=pos(l-j-1);
                 if(j==0) t[c[j]-'a'+1].b=1;
             }
         }
         sort(t+1,t+11,cmp);
         for(int i=1;i<=10;i++){
             if(t[i].b==0 && t[i].a!=0){
                 t[i].a=0;
                 break;
             }
         }
         int ans=0,sum=1;
         for(int i=1;i<=10;i++){
             if(t[i].a!=0){
                 ans+=t[i].a*sum;
                 sum++;
             }
         }
         cout<<ans<<endl;
     }
     ```

2. **作者：codeLJH114514 (4星)**
   - **关键亮点**：使用结构体存储字母的权重和是否为首字母，排序后优先为权重大的字母分配较小的数字，特别处理不能为0的情况，代码结构清晰。
   - **代码核心**：
     ```cpp
     struct Node{
         int v, k;
         bool t;
         char ch;
         bool operator<(const Node& n) const& {
             return k > n.k;
         }
     } d[12];
     int main() {
         cin >> n;
         for (int i = 1; i <= 10; i++) d[i].ch = i + 'a' - 1;
         for (int i = 1; i <= n; i++) {
             cin >> s;
             d[s[0] - 'a' + 1].t = true;
             for (int j = 0; j < s.size(); j++)
                 d[s[j] - 'a' + 1].k += pow(10, s.size() - j - 1);
         }
         sort(d + 1, d + 10 + 1);
         int zero = 0;
         for (int i = 1; i <= 10; i++) {
             if (not d[i].t) {
                 zero = i;
                 break;
             }
         }
         for (int i = 1; i <= 10; i++) d[i].v = -1;
         d[zero].v = 0;
         int cnt = 1;
         for (int i = 1; i <= 10; i++)
             if (d[i].v == -1)
                 d[i].v = cnt++;
         int ans = 0;
         for (int i = 1; i <= 10; i++)
             ans += d[i].v * d[i].k;
         cout << ans;
     }
     ```

3. **作者：_frog (4星)**
   - **关键亮点**：使用结构体存储字母的权重和是否为首字母，排序后优先为权重大的字母分配较小的数字，特别处理不能为0的情况，代码结构清晰，时间复杂度分析详细。
   - **代码核心**：
     ```cpp
     struct Node {
         bool can_be_0;
         ll val;
         char name;
     } a[11];
     bool cmp(Node x, Node y) {
         if (x.val != y.val)return x.val < y.val;
         return x.name < y.name;
     }
     int main() {
         cin >> n;
         for (ll i = 0; i < n; i++) {
             cin >> str[i];
             flg[str[i][0] - 'a'] = 1;
             ll s = 1;
             for (ll j = str[i].length() - 1; j >= 0; j--) {
                 t[str[i][j] - 'a'] += s;
                 s *= 10;
             }
         }
         for (ll i = 0; i < 10; i++) {
             a[i].can_be_0 = !flg[i];
             a[i].name = i + 'a';
             a[i].val = t[i];
         }
         sort(a, a + 10, cmp);
         for (ll i = 9; i >= 0; i--) {
             if (a[i].can_be_0) {
                 zero_ind = i;
                 break;
             }
         }
         ll w = 9;
         for (ll i = 0; i < 10; i++) {
             if (i == zero_ind) {
                 continue;
             }
             ans += a[i].val * w;
             w--;
         }
         cout << ans;
     }
     ```

【最优关键思路或技巧】
- **权重计算**：通过计算每个字母在所有字符串中的位置对应的10的幂次和，确定其权重。
- **贪心策略**：根据权重从大到小排序，优先为权重大的字母分配较小的数字，以确保最终的和最小。
- **前导零处理**：特别处理不能为0的字母（即作为字符串的首字母），确保没有前导零。

【可拓展之处】
- **类似问题**：可以扩展到其他进制的问题，或者字母与数字的映射关系不同的问题。
- **优化思路**：可以考虑使用更高效的数据结构来存储和排序字母的权重，如优先队列。

【推荐题目】
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：56.60秒