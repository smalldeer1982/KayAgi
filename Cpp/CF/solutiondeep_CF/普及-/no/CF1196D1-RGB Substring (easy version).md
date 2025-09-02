# 题目信息

# RGB Substring (easy version)

## 题目描述

The only difference between easy and hard versions is the size of the input.

You are given a string $ s $ consisting of $ n $ characters, each character is 'R', 'G' or 'B'.

You are also given an integer $ k $ . Your task is to change the minimum number of characters in the initial string $ s $ so that after the changes there will be a string of length $ k $ that is a substring of $ s $ , and is also a substring of the infinite string "RGBRGBRGB ...".

A string $ a $ is a substring of string $ b $ if there exists a positive integer $ i $ such that $ a_1 = b_i $ , $ a_2 = b_{i + 1} $ , $ a_3 = b_{i + 2} $ , ..., $ a_{|a|} = b_{i + |a| - 1} $ . For example, strings "GBRG", "B", "BR" are substrings of the infinite string "RGBRGBRGB ..." while "GR", "RGR" and "GGG" are not.

You have to answer $ q $ independent queries.

## 说明/提示

In the first example, you can change the first character to 'R' and obtain the substring "RG", or change the second character to 'R' and obtain "BR", or change the third, fourth or fifth character to 'B' and obtain "GB".

In the second example, the substring is "BRG".

## 样例 #1

### 输入

```
3
5 2
BGGGG
5 3
RBRGR
5 5
BBBRR
```

### 输出

```
1
0
3
```

# AI分析结果

### 题目内容
#### RGB子串（简单版本）
##### 题目描述
简单版本和困难版本的唯一区别在于输入规模。

给定一个由 $n$ 个字符组成的字符串 $s$，每个字符为 'R'、'G' 或 'B'。

同时给定一个整数 $k$。你的任务是修改初始字符串 $s$ 中最少数量的字符，使得修改后存在一个长度为 $k$ 的子串，该子串既是 $s$ 的子串，也是无限字符串 “RGBRGBRGB...” 的子串。

如果存在正整数 $i$ 使得 $a_1 = b_i$，$a_2 = b_{i + 1}$，$a_3 = b_{i + 2}$，...，$a_{|a|} = b_{i + |a| - 1}$，则字符串 $a$ 是字符串 $b$ 的子串。例如，字符串 “GBRG”、“B”、“BR” 是无限字符串 “RGBRGBRGB...” 的子串，而 “GR”、“RGR” 和 “GGG” 不是。

你需要回答 $q$ 个独立的查询。
##### 说明/提示
在第一个示例中，你可以将第一个字符改为 'R' 得到子串 “RG”，或将第二个字符改为 'R' 得到 “BR”，或将第三个、第四个或第五个字符改为 'B' 得到 “GB”。

在第二个示例中，子串是 “BRG”。
##### 样例 #1
- **输入**
```
3
5 2
BGGGG
5 3
RBRGR
5 5
BBBRR
```
- **输出**
```
1
0
3
```

### 算法分类
枚举

### 综合分析与结论
所有题解思路本质相同，均基于数据范围小，采用枚举法解题。先明确无限字符串 “RGBRGBRGB...” 长度为 $k$ 的子串仅有 “RGB”、“GBR”、“BRG” 这三种循环排列情况。然后对每种排列，枚举原字符串 $s$ 中长度为 $k$ 的子串，对比计算需修改的字符数，取三种排列情况中的最小值作为结果。各题解主要差异在代码实现细节，如变量命名、函数封装、输入输出优化等方面。

### 所选的题解
- **EatBread（3星）**
  - **关键亮点**：代码简洁明了，逻辑直接。将三种循环情况分别处理，通过函数 `jjss` 计算每种情况下子串需修改的字符数，再在 `js` 函数中枚举原串所有可能子串位置取最小值，最后在 `main` 函数中遍历三种循环情况得出最终结果。
  - **核心代码**：
```cpp
int jjss(int t,int w)
{
    int ans=0;
    for(int i=t; i<w; i++){if(s[i]!=h[(i-t)%3])ans++;}
    return ans;
}
int js()
{
    int t=0,ans=100000,w=b;
    while(w<=a)
    {
        ans=min(jjss(t,w),ans);
        t++,w++;
    }
    return ans;
}
int main()
{
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        scanf("%d%d",&a,&b);cin>>s;gs=10000000;
        h[0]='R',h[1]='G',h[2]='B';gs=min(gs,js());
        h[0]='G',h[1]='B',h[2]='R';gs=min(gs,js());
        h[0]='B',h[1]='R',h[2]='G';gs=min(gs,js());
        cout<<gs<<endl;
    }
    return 0;
} 
```
  - **核心实现思想**：`jjss` 函数计算特定子串与目标循环排列的差异字符数，`js` 函数遍历原串所有可能子串位置找最小差异值，`main` 函数遍历三种循环排列得出最终最小修改字符数。
- **crashed（2星）**
  - **关键亮点**：对每种起始匹配字符（R、G、B）分别处理，通过预处理数组 `base` 记录每种起始匹配下对应位置应有的字符。在 `solve` 函数中通过滑动窗口思想，动态更新窗口内与目标匹配不符的字符数，从而优化计算过程。
  - **核心代码**：
```cpp
void init()
{
    for( int j = 1 ; j <= 3 ; j ++ )
    {
        for( int i = 1 ; i <= 2000 ; i ++ )
        {
            base[j - 1][i] = ( j + i - 2 ) % 3 + 1;
        }
    }
}
int solve( const int sta )
{
    int cnt = 0, i;
    for( i = 1 ; i <= K ; i ++ )
    {
        cnt += ( a[i]!= base[sta][i] );
    }
    int res = cnt;
    for( ; i <= N ; i ++ )
    {
        cnt -= ( a[i - K]!= base[sta][i - K] );
        cnt += ( a[i]!= base[sta][i] );
        res = MIN( res, cnt );
    }
    return res;
}
int main()
{
    int Q, res;
    read( Q );
    init();
    while( Q -- )
    {
        read( N ), read( K );
        scanf( "%s", str + 1 );
        for( int i = 1 ; i <= N ; i ++ )
        {
            a[i] = trans( str[i] );
        }
        res = 0x3f3f3f3f;
        for( int i = 0 ; i < 3 ; i ++ )
        {
            res = MIN( res, solve( i ) );
        }
        write( res ), putchar( '\n' );
    }
    return 0;
}
```
  - **核心实现思想**：`init` 函数预处理出每种起始匹配下各位置应有的字符。`solve` 函数先计算初始窗口内不符字符数，再通过滑动窗口动态更新不符字符数并取最小值。`main` 函数读入数据，对三种起始匹配情况调用 `solve` 函数取最小值输出。
- **封禁用户（1星）**
  - **关键亮点**：代码直观，直接在循环中枚举原字符串所有长度为 $k$ 的子串，对每个子串分别按 “RGB”、“GBR”、“BRG” 三种排列计算需修改的字符数，取最小值作为结果。
  - **核心代码**：
```cpp
int main()
{
    cin>>q;
    for(int i=1; i<=q; i++)
    {
        cin>>n>>k>>s;
        t=0,w=k,x=0,mi=2147483647;
        while(w<=n)
        {
            for(int j=t; j<w; j++)
            {
                if(j%3==0&&s[j]!='R')x++;
                if(j%3==1&&s[j]!='G')x++;
                if(j%3==2&&s[j]!='B')x++;
            }
            mi=min(mi,x),x=0;
            for(int j=t; j<w; j++)
            {
                if(j%3==0&&s[j]!='G')x++;
                if(j%3==1&&s[j]!='B')x++;
                if(j%3==2&&s[j]!='R')x++;
            }
            mi=min(mi,x),x=0;
            for(int j=t; j<w; j++)
            {
                if(j%3==0&&s[j]!='B')x++;
                if(j%3==1&&s[j]!='R')x++;
                if(j%3==2&&s[j]!='G')x++;
            }
            mi=min(mi,x),x=0;
            t++,w++;
        }
        cout<<mi<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：通过外层 `while` 循环枚举原串所有长度为 $k$ 的子串，内层三个 `for` 循环分别按三种排列计算子串需修改字符数，每次更新最小值，最终输出结果。

### 最优关键思路或技巧
- **固定模式枚举**：认识到目标子串只有 “RGB”、“GBR”、“BRG” 这三种固定循环排列模式，对每种模式枚举原串所有长度为 $k$ 的子串进行对比，简化问题求解。
- **滑动窗口优化**：如 `crashed` 的题解，通过滑动窗口思想动态更新窗口内与目标匹配不符的字符数，减少重复计算，一定程度优化枚举效率。

### 拓展思路
此类题目拓展方向可从增加数据规模、改变目标字符串模式、增加限制条件等方面入手。例如，若数据规模增大，单纯枚举会超时，可能需结合其他优化算法，如哈希、后缀数组等；若目标字符串模式更复杂，需更深入分析模式特点以优化枚举方式。

### 相似知识点洛谷题目
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：通过枚举解决组合问题，锻炼枚举思路。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串相关枚举题目，需在字符串中枚举匹配特定单词，与本题在字符串中枚举子串思路类似。
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：利用枚举解决组合选数问题，可加强枚举算法运用能力。

### 个人心得摘录与总结
无。 

---
处理用时：100.76秒