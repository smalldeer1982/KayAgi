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
给定一个由小写拉丁字母组成的字符串 $s$，用 $|s|$ 表示该字符串的长度，字符串中的字符从 $1$ 开始编号。

你的任务是判断是否可以重新排列字符串 $s$ 中的字符，使得对于任何小于等于 $|s|$ 的质数 $p$ 以及任何范围在 $1$ 到 $|s|/p$（包含两端）的整数 $i$，都满足 $s_{p}=s_{p×i}$。如果答案是肯定的，找出一种重新排列字符的方法。

## 说明/提示
在第一个样例中，六个可能的字符串中的任何一个都可以："abc"、"acb"、"bac"、"bca"、"cab" 或 "cba"。

在第二个样例中，没有字母排列能满足 $p = 2$ 时的条件（$s_{2}=s_{4}$）。

在第三个测试中，任何字符 "y" 不占据位置 2、3、4、6 的字符串都是有效的。

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
这些题解的核心思路都是先分析出字符串需要满足的条件，即存在一个大集合（由质数及其倍数位置构成），大集合中的字符需相同，然后统计大集合的规模，判断是否有字符的出现次数不小于该规模，若有则有解，否则无解。有解时将大集合位置用该字符填充，其余位置随意填充。

各题解的算法要点和难点对比如下：
- **Oscar12345**：先初始化质数标记数组，再统计大集合规模，最后根据字符数量判断并构造解。难点在于正确标记质数和计算大集合规模。
- **qwertim**：通过判断质数和合数，统计大集合规模，找出出现次数最多的字符进行判断和构造。难点在于准确判断质数和统计大集合元素个数。
- **Lily_White**：利用标记数组找出大集合元素，排序统计字符数量，判断并构造解。难点在于找出大集合元素和正确统计字符数量。
- **__hjwucj__**：与 qwertim 思路类似，通过判断质数和合数统计大集合规模，判断并构造解。难点在于质数判断和大集合规模统计。
- **Rei_Sen**：从图论角度分析，得出大集合和单点的结论，用筛法预处理质数，计算大集合规模并判断构造解。难点在于图论分析和质数筛法的实现。

### 题解评分
- **Oscar12345**：4星。思路清晰，代码结构完整，对质数标记和大集合规模计算有详细实现。
- **qwertim**：4星。思路简洁明了，代码可读性高，利用简单的循环和判断实现核心逻辑。
- **Lily_White**：3星。思路正确，但代码中使用了较多自定义宏和复杂的输入输出函数，影响代码可读性。
- **__hjwucj__**：3星。思路与 qwertim 类似，但代码中存在一些不规范的注释和命名，影响整体质量。
- **Rei_Sen**：3星。从图论角度分析有一定创新性，但代码中复杂度分析不够严谨，且部分注释不够清晰。

### 所选题解
- **Oscar12345**（4星）
  - 关键亮点：思路清晰，代码结构完整，对质数标记和大集合规模计算有详细实现。
- **qwertim**（4星）
  - 关键亮点：思路简洁明了，代码可读性高，利用简单的循环和判断实现核心逻辑。

### 重点代码
#### Oscar12345
```cpp
void init ()
{
    memset ( maxPrime , -1 , sizeof ( maxPrime ) );
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
    while (~scanf ( "%s" , s ) )
    {
        int n = strlen ( s );
        memset ( mark , 0 , sizeof ( mark ) );
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
        memset ( num , 0 , sizeof ( num ));
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
核心实现思想：先初始化质数标记数组，再统计大集合规模，然后统计字符数量，判断是否有字符数量满足大集合规模，若有则构造解。

#### qwertim
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
核心实现思想：先判断质数和合数，统计大集合规模，找出出现次数最多的字符，判断是否满足条件，若满足则构造解。

### 最优关键思路或技巧
- **思维方式**：将问题转化为判断是否有字符的出现次数能满足大集合规模，利用质数及其倍数的关系找出大集合。
- **代码实现技巧**：使用标记数组标记大集合元素，使用哈希表统计字符数量。

### 可拓展之处
同类型题可能会改变字符串的限制条件，如增加更多的位置关系限制，或者改变字符的种类和数量。类似算法套路可以是先分析问题的约束条件，找出关键集合，然后根据集合规模和元素数量进行判断和构造。

### 推荐洛谷题目
- P1217 [USACO1.5] 回文质数 Prime Palindromes
- P1075 质因数分解
- P2014 [CTSC1997]选课

### 个人心得摘录与总结
- **Rei_Sen**：提到由于试药导致代码可能晕乎，从图论角度分析问题，得出大集合和单点的结论，体现了从不同角度思考问题的重要性。 

---
处理用时：65.39秒