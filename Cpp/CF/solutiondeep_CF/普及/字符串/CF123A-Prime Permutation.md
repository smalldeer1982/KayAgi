# 题目信息

# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc
```

### 输出

```
YES
abc
```

## 样例 #2

### 输入

```
abcd
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
xxxyxxx
```

### 输出

```
YES
xxxxxxy
```

# AI分析结果

### 题目中文重写
# 质数排列

## 题目描述
给定一个由小写拉丁字母组成的字符串 $s$，设字符串的长度为 $|s|$，字符串中的字符从 $1$ 开始编号。

你的任务是判断是否可以重新排列字符串 $s$ 中的字符，使得对于任何小于等于 $|s|$ 的质数 $p$ 以及任何范围在 $1$ 到 $|s|/p$（包含两端）的整数 $i$，都满足 $s_{p}=s_{p×i}$。如果答案是肯定的，找出一种重新排列字符的方法。

## 说明/提示
在第一个样例中，六个可能的字符串 “abc”、“acb”、“bac”、“bca”、“cab” 或 “cba” 都满足条件。

在第二个样例中，没有字母排列能满足 $p = 2$ 时的条件（$s_{2}=s_{4}$）。

在第三个样例中，任何字符 “y” 不占据位置 2、3、4、6 的字符串都是有效的。

## 样例 #1
### 输入
```
abc
```
### 输出
```
YES
abc
```

## 样例 #2
### 输入
```
abcd
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
xxxyxxx
```
### 输出
```
YES
xxxxxxy
```

### 综合分析与结论
这些题解的核心思路都是将字符串中的字符按特定规则分组，判断是否有足够数量的同一字符来填充特定位置。具体来说，都发现了字符串会被分成一个大集合和若干小集合，大集合中的元素需要填入相同字符。

- **思路对比**：
    - Oscar12345 通过标记质数和其倍数，找出大集合规模，判断是否有字母数量足够。
    - qwertim 和 __hjwucj__ 计算所有合数和小于 $\frac{|s|}{2}$ 的质数的数量，判断出现次数最多的字符是否足够。
    - Lily_White 从字符填充规则出发，将字符串分组，判断最大字符数量是否满足大集合需求。
    - Rei_Sen 从图和并查集角度分析，最后简化为计算特定染色次数判断。
- **算法要点**：
    - 都需要统计字符出现次数。
    - 确定大集合的规模或需要相同字符填充的位置数量。
    - 判断是否有足够数量的同一字符。
    - 若有解，构造符合条件的字符串。
- **解决难点**：
    - 找出字符串分组的规律，确定大集合的构成。
    - 高效计算大集合的规模。
    - 合理构造满足条件的字符串。

### 所选题解
- **Oscar12345（5星）**
    - **关键亮点**：思路清晰，代码实现规范，通过预处理质数信息，逐步标记位置，逻辑严谨。
    - **核心代码**：
```cpp
void init ()
{
    memset ( maxPrime, -1, sizeof ( maxPrime ) );
    for ( int i = 2 ; i < MAX ; i++ )
    {
        if (~maxPrime[i]) continue;
        for ( int j = i*2 ; j < MAX ; j += i )
            maxPrime[j] = i;
    }
}

int main ( )
{
    init ();
    while (~scanf ( "%s", s ) )
    {
        int n = strlen ( s );
        memset ( mark, 0, sizeof ( mark ) );
        if ( n < 4 )
        {
            puts ( "YES" );
            puts ( s );
            continue;
        }
        int cnt = 2;
        for ( int i = n ; i >= 2; i-- )
        {
            if ( mark[i] && maxPrime[i] == -1 ) continue;
            if ( ~maxPrime[i] )
            {
                mark[i] = true;
                for ( int j = 2 ; j*j <= i ; j++ )
                {
                    if ( i%j ) continue;
                    mark[j] = mark[i/j] = true;
                }
            }
            else cnt++;
        }
        memset ( num, 0, sizeof ( num ));
        for ( int i = 0 ; i < n ; i++ )
            num[s[i]-97]++;
        int id = -1;
        for ( int i = 0 ; i < 26 ; i++ )
            if ( n-cnt+1 <= num[i] )
            {
                id = i;
                num[i] -= (n-cnt+1);
                break;
            }
        if ( id == -1 )
        {
            puts ( "NO" );
            continue;
        }
        for ( int i = 0 ; i < n ; i++ )
        {
            if ( mark[i+1] ) s[i] =(char)(id+97);
            else
            for ( int j = 0 ; j < 26 ; j++ )
                if ( num[j] )
                {
                    num[j]--;
                    s[i] = (char)(j+97);
                    break;
                }
        }
        puts ( "YES");
        puts ( s );
    }
}
```
    - **核心实现思想**：先预处理质数信息，然后遍历字符串长度，标记需要相同字符填充的位置，统计大集合规模。接着统计字符出现次数，判断是否有足够数量的字符，若有则构造结果字符串。
- **qwertim（4星）**
    - **关键亮点**：思路简洁明了，代码使用了 `map` 统计字符出现次数，逻辑清晰。
    - **核心代码**：
```cpp
bool isprime(int x){//判断是不是质数
    int tmp=sqrt(x);
    fo(i,2,tmp)
        if(x%i==0)return 0;
    return 1;
}
int main(){
    cin>>s;
    fo(i,0,s.size()-1)mp[s[i]]++;
    for(auto it:mp)
        if(maxn<it.second)maxn=it.second,c=it.first;//求出出现次数最多的字符以及出现次数
    fo(i,2,s.size()){
        if(!isprime(i))b[i]=1,a++;//是合数
        else if(i<=s.size()/2)b[i]=1,a++;//是|s|/2及以下的质数
    }
    if(maxn<a)return cout<<"NO",0;//填不满则直接输出NO
    puts("YES"),mp[c]-=a;
    fo(i,1,s.size())
        if(b[i])ans[i]=c;//符合要求的都填上
    for(auto it:mp)
        fo(i,1,it.second){
            while(ans[pos]==c)pos++;//依次找出没有填过的
            ans[pos++]=it.first;
        }
    fo(i,1,s.size())cout<<ans[i];
    return 0;
}
```
    - **核心实现思想**：先判断质数，然后统计字符出现次数，找出出现次数最多的字符。接着计算需要相同字符填充的位置数量，判断是否有足够字符，若有则构造结果字符串。
- **Lily_White（4星）**
    - **关键亮点**：从字符填充规则出发，使用 `vector` 存储大集合位置，逻辑清晰。
    - **核心代码**：
```cpp
int main() {
    scanf("%s", s + 1); int n = strlen(s + 1);
    for (int i = 2; i <= n; i++){
        if (i == 1) continue;
        if (!mark[i]) {
            mark[i] = true;
            if (n / i <= 1) continue;			
            pos.pb(i);
            for (int j = i; j <= n; j += i) {
                if (!mark[j]) {
                    mark[j] = true;
                    pos.pb(j);
                }
            }
        }
    }
    sort(s + 1, s + n + 1);
    repn(i, n) {
        if (s[i]!= s[i - 1]) cnt++;
        chr[cnt] = s[i];
        sz[cnt]++;
    }
    int maxv, maxi = 0;
    maxv = -INF;
    repn(i, cnt) {
        if (sz[i] > maxv) {
            maxv = sz[i];
            maxi = i;
        }
    }
    if (maxv < (int)pos.size()) {
        cout << "NO" << endl;
        return 0;
    }
    else {
        puts("YES");
        for (auto i:pos) ans[i] = chr[maxi], sz[maxi]--;
        for (int i = 1; i <= n; i++) {
            if (ans[i]) continue;
            for (int j = 1; j <= cnt; j++) {
                if (sz[j]) {
                    ans[i] = chr[j];
                    sz[j]--;
                    break;
                } 
            }
        }
        printf("%s\n", ans + 1);
    }
    return 0;
}
```
    - **核心实现思想**：遍历字符串长度，标记需要相同字符填充的位置并存储在 `vector` 中。统计字符出现次数，找出最大字符数量，判断是否满足大集合需求，若满足则构造结果字符串。

### 最优关键思路或技巧
- 发现字符串分组规律，将问题转化为判断是否有足够数量的同一字符填充大集合。
- 预处理质数信息，高效计算大集合规模。

### 可拓展之处
同类型题可能会改变字符填充规则或增加其他限制条件，类似算法套路是分析问题的约束条件，找出分组规律，通过统计和判断来解决问题。

### 洛谷相似题目推荐
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
- [P1075 [NOIP2012 普及组] 质因数分解](https://www.luogu.com.cn/problem/P1075)
- [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)

### 个人心得摘录与总结
- Rei_Sen 提到由于试药可能导致代码写得晕乎，但通过深入分析问题性质，从图和并查集角度出发，最终简化问题，得出高效解法。总结：在解决问题时，可从不同角度思考，挖掘问题的潜在性质，简化问题求解。 

---
处理用时：73.66秒