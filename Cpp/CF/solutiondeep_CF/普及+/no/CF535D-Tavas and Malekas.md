# 题目信息

# Tavas and Malekas

## 题目描述

Tavas is a strange creature. Usually "zzz" comes out of people's mouth while sleeping, but string $ s $ of length $ n $ comes out from Tavas' mouth instead.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535D/edec2eae8d180d77009c457fa18d1007b3d9ea05.png)Today Tavas fell asleep in Malekas' place. While he was sleeping, Malekas did a little process on $ s $ . Malekas has a favorite string $ p $ . He determined all positions $ x_{1}&lt;x_{2}&lt;...&lt;x_{k} $ where $ p $ matches $ s $ . More formally, for each $ x_{i} $ ( $ 1<=i<=k $ ) he condition $ s_{xi}s_{xi}+1...\ s_{xi}+|p|-1=p $ is fullfilled.

Then Malekas wrote down one of subsequences of $ x_{1},x_{2},...\ x_{k} $ (possibly, he didn't write anything) on a piece of paper. Here a sequence $ b $ is a subsequence of sequence $ a $ if and only if we can turn $ a $ into $ b $ by removing some of its elements (maybe no one of them or all).

After Tavas woke up, Malekas told him everything. He couldn't remember string $ s $ , but he knew that both $ p $ and $ s $ only contains lowercase English letters and also he had the subsequence he had written on that piece of paper.

Tavas wonders, what is the number of possible values of $ s $ ? He asked SaDDas, but he wasn't smart enough to solve this. So, Tavas asked you to calculate this number for him.

Answer can be very large, so Tavas wants you to print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample test all strings of form "ioioi?" where the question mark replaces arbitrary English letter satisfy.

Here $ |x| $ denotes the length of string x.

Please note that it's possible that there is no such string (answer is 0).

## 样例 #1

### 输入

```
6 2
ioi
1 3
```

### 输出

```
26
```

## 样例 #2

### 输入

```
5 2
ioi
1 2
```

### 输出

```
0
```

# AI分析结果

### 题目重写
# Tavas和Malekas

## 题目描述
Tavas是一种奇怪的生物。通常人们睡觉时会从嘴里发出“zzz”，但Tavas睡觉时从嘴里发出的是长度为n的字符串s。

今天Tavas在Malekas的住处睡着了。在他睡觉的时候，Malekas对s做了一个小操作。Malekas有一个喜欢的字符串p。他确定了所有p与s匹配的位置x1 < x2 <... < xk 。更正式地说，对于每个xi（1 <= i <= k），都满足sxi sxi+1... sxi+|p|-1 = p这个条件。

然后Malekas在一张纸上写下了x1, x2,... xk的一个子序列（也可能什么都没写）。这里序列b是序列a的子序列，当且仅当我们可以通过删除a的一些元素（也许一个都不删，或者全删）将a变成b。

Tavas醒来后，Malekas把一切都告诉了他。他不记得字符串s了，但他知道p和s都只包含小写英文字母，而且他有Malekas写在纸上的子序列。

Tavas想知道，s可能的值有多少个？他问了SaDDas，但他不够聪明，无法解决这个问题。所以，Tavas请你为他计算这个数字。

答案可能非常大，所以Tavas希望你输出答案对10^9 + 7取模的结果。

## 说明/提示
在第一个样例测试中，所有形如“ioioi?”的字符串都满足条件，其中问号可以替换为任意英文字母。

这里|x|表示字符串x的长度。

请注意，有可能不存在这样的字符串（答案为0）。

## 样例 #1
### 输入
```
6 2
ioi
1 3
```
### 输出
```
26
```
## 样例 #2
### 输入
```
5 2
ioi
1 2
```
### 输出
```
0
```

### 算法分类
字符串

### 综合分析与结论
这些题解主要围绕判断给定模式串在文本串中出现位置的合法性，并计算未被模式串覆盖位置数来得出可能的文本串数量。核心思路是先判断模式串出现位置是否合法，若合法则计算空白位置数，答案即为26的空白位置数次幂。解决难点在于判断相邻模式串重叠部分是否匹配，不同题解采用了不同方法，如Z函数、KMP算法、字符串哈希等。

### 所选的题解
- **作者：tuzhewen（5星）**
    - **关键亮点**：使用Z函数判断位置合法性，思路清晰，代码实现简洁明了，详细注释便于理解。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
void get_z(char *s1,int n) {
    int L=0,R=0;
    F(i,1,n-1) {
        if(i>R) {
            L=i,R=i;
            while(R<n&&s1[R-L]==s1[R])R++;
            z[i]=--R-L+1;
        }
        else {
            int k=i-L;
            if(z[k]<R-i+1)z[i]=z[k];
            else {
                L=i;
                while(R<n&&s1[R-L]==s1[R]) R++;
                z[i]=--R-L+1;
            }
        }
    }
}
int ans,sum[N],ls;
bool check(int x,int y) {
    if(y-x>=lenp) return true;
    return z[y-x]>=x+lenp-y;
}
```
核心实现思想：`get_z`函数用于计算Z数组，`check`函数通过Z数组判断两个位置是否冲突。
- **作者：Computer1828（4星）**
    - **关键亮点**：利用哈希判断相邻模式串是否合法，通过图示辅助理解，代码简洁高效。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
bool vis[N];
int main(){
    scanf("%d%d",&n,&m);
    if(m == 0) return printf("%lld",qpow(26,n)),0;
    scanf("%s",p+1);int len = strlen(p+1);
    pw[0] = 1;
    for(int i = 1;i<=len;++i) pre[i] = (pre[i-1]*26+(p[i]-'a'))%mm,pw[i] = pw[i-1]*26%mm;
    for(int i = len;i>=1;--i) suf[i] = (suf[i+1]+1ll*(p[i]-'a')*pw[len-i])%mm;
    scanf("%d",&a[1]);
    for(int i = 0;i<len;++i) vis[a[1]+i] = true;
    for(int i = 2;i<=m;++i){
        scanf("%d",a+i);
        if(a[i-1]+len-1 >= a[i]){
            if(suf[a[i]-a[i-1]+1]!= pre[a[i-1]+len-a[i]]) return printf("0"),0;
            else for(int j = a[i-1]+len;j<=a[i]+len-1;++j) vis[j] = true;
        }else for(int j = a[i];j<=a[i]+len-1;++j) vis[j] = true;
    }
    ll ans = 0;
    for(int i = 1;i<=n;++i) if(!vis[i]) ans++;
    printf("%lld",qpow(26,ans));
    return 0;
}
```
核心实现思想：先预处理模式串前缀和后缀的哈希值，在遍历模式串位置时，通过比较哈希值判断相邻模式串重叠部分是否匹配。
- **作者：fighter（4星）**
    - **关键亮点**：详细分析题意，分别介绍KMP和字符串哈希两种判断重叠部分匹配的方法，代码实现完整且有注释。
    - **个人心得**：无
    - **KMP核心代码片段**：
```cpp
void init(){
    int j = 0;
    len = strlen(s+1);
    for(int i = 2; i <= len; i++){
        while(j && s[j+1]!= s[i]){
            j = Next[j];
        }
        if(s[j+1] == s[i]) j++;
        Next[i] = j;
    }
    for(int i = len; i; i = Next[i]){
        mark[i] = 1;
    }
}
int main()
{
    cin >> n >> m;
    scanf("%s", s+1);
    init();
    for(int i = 1; i <= m; i++){
        scanf("%d", &p[i]);
    }
    if(!m){
        cout << qpow(26, n) << endl;
        return 0;
    }
    for(int i = 1; i <= m; i++){
        if(p[i]+len-1 > n){
            puts("0");
            return 0;
        }
        if(i > 1 && p[i-1]+len > p[i]){
            int x = p[i-1]+len-p[i];
            if(!mark[x]){
                puts("0");
                return 0;
            }
        }
    }
    int cnt = p[1]-1;
    for(int i = 1; i < m; i++){
        if(p[i]+len < p[i+1]){
            cnt += p[i+1]-p[i]-len;
        }
    }
    cnt += n-p[m]-len+1;
    cout << qpow(26, cnt) << endl;
    
    return 0;
}
```
核心实现思想：`init`函数通过KMP算法计算Next数组，并标记出可能匹配的重叠位置长度，在`main`函数中遍历模式串位置，判断是否合法并计算空白位置数。
    - **字符串哈希核心代码片段**：
```cpp
void init(){
    len = strlen(s+1);
    p1[0] = 1;
    for(int i = 1; i <= len; i++){
        p1[i] = p1[i-1]*b1%p;
    }
    p2[0] = 1;
    for(int i = 1; i <= len; i++){
        p2[i] = p2[i-1]*b2%q;
    }
    sum1[0] = 0;
    for(int i = 1; i <= len; i++){
        sum1[i] = (sum1[i-1]*b1%p+s[i]-'a')%p;
    }
    sum2[0] = 0;
    for(int i = 1; i <= len; i++){
        sum2[i] = (sum2[i-1]*b2%q+s[i]-'a')%q;
    }
}
int main()
{
    cin >> n >> m;
    scanf("%s", s+1);
    init();
    for(int i = 1; i <= m; i++){
        scanf("%d", &a[i]);
    }
    if(!m){
        cout << qpow(26, n) << endl;
        return 0;
    }
    for(int i = 1; i <= m; i++){
        if(a[i]+len-1 > n){
            puts("0");
            return 0;
        }
        if(i > 1 && a[i-1]+len > a[i]){
            int x = a[i-1]+len-a[i];
            if(sum1[x]!=(sum1[len]%p-sum1[len-x]*p1[x]%p+p)%p || sum2[x]!=(sum2[len]-sum2[len-x]*p2[x]%q+q)%q){
                puts("0");
                return 0;
            }
        }
    }
    
    int cnt = a[1]-1;
    for(int i = 1; i < m; i++){
        if(a[i]+len < a[i+1]){
            cnt += a[i+1]-a[i]-len;
        }
    }
    cnt += n-a[m]-len+1;
    cout << qpow(26, cnt) << endl;
    
    return 0;
}
```
核心实现思想：`init`函数预处理模式串的双哈希值，在`main`函数中遍历模式串位置，通过比较双哈希值判断相邻模式串重叠部分是否匹配，并计算空白位置数。

### 最优关键思路或技巧
利用字符串相关算法（如Z函数、KMP、字符串哈希）判断相邻模式串重叠部分的匹配情况，从而确定文本串的合法性。这种通过分析字符串局部特征来解决整体问题的思维方式，以及利用相关算法高效实现的技巧是关键。

### 拓展
同类型题通常围绕字符串匹配、子串计数等问题展开，类似算法套路包括利用字符串匹配算法（如AC自动机等）解决多模式串匹配问题。

### 推荐题目
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
- [P5410 【模板】Z函数](https://www.luogu.com.cn/problem/P5410)
- [P4391 [BOI2009]Radio Transmission 无线传输](https://www.luogu.com.cn/problem/P4391)

### 个人心得摘录与总结
无

---
处理用时：93.42秒