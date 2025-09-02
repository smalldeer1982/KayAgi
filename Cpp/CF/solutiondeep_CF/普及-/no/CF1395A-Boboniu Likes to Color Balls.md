# 题目信息

# Boboniu Likes to Color Balls

## 题目描述

Boboniu gives you

- $ r $ red balls,
- $ g $ green balls,
- $ b $ blue balls,
- $ w $ white balls.

He allows you to do the following operation as many times as you want:

- Pick a red ball, a green ball, and a blue ball and then change their color to white.

You should answer if it's possible to arrange all the balls into a palindrome after several (possibly zero) number of described operations.

## 说明/提示

In the first test case, you're not able to do any operation and you can never arrange three balls of distinct colors into a palindrome.

In the second test case, after doing one operation, changing $ (8,1,9,3) $ to $ (7,0,8,6) $ , one of those possible palindromes may be "rrrwwwbbbbrbbbbwwwrrr".

A palindrome is a word, phrase, or sequence that reads the same backwards as forwards. For example, "rggbwbggr", "b", "gg" are palindromes while "rgbb", "gbbgr" are not. Notice that an empty word, phrase, or sequence is palindrome.

## 样例 #1

### 输入

```
4
0 1 1 1
8 1 9 3
0 0 0 0
1000000000 1000000000 1000000000 1000000000```

### 输出

```
No
Yes
Yes
Yes```

# AI分析结果

### 题目内容
# Boboniu喜欢给球涂色

## 题目描述
Boboniu给你：
 - $r$ 个红球
 - $g$ 个绿球
 - $b$ 个蓝球
 - $w$ 个白球

他允许你按照如下操作，次数不限：
 - 选择一个红球、一个绿球和一个蓝球，然后将它们的颜色都变成白色。

你需要回答，经过若干次（可能为零次）上述操作后，是否能将所有球排列成一个回文序列。

## 说明/提示
在第一个测试用例中，你无法进行任何操作，并且你永远无法将三个不同颜色的球排列成回文序列。

在第二个测试用例中，经过一次操作，将 $(8, 1, 9, 3)$ 变为 $(7, 0, 8, 6)$ ，其中一种可能的回文序列可以是 “rrrwwwbbbbrbbbbwwwrrr” 。

回文是一个单词、短语或序列，从前往后读和从后往前读是一样的。例如，“rggbwbggr”、“b”、“gg” 是回文，而 “rgbb”、“gbbgr” 不是。注意，空单词、短语或序列也是回文。

## 样例 #1
### 输入
```
4
0 1 1 1
8 1 9 3
0 0 0 0
1000000000 1000000000 1000000000 1000000000
```
### 输出
```
No
Yes
Yes
Yes
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于奇偶性分析来判断是否能构成回文序列。因为回文序列要求球个数为奇数的颜色种类最多为1种，而每次操作会改变四种球个数的奇偶性，且操作两次奇偶性不变，所以最多考虑操作一次后的情况。难点在于全面考虑各种情况，比如球数为0时无法操作的特殊情况。各题解在实现上略有不同，有的通过直接判断奇偶个数，有的通过分情况讨论球数为0的情况等。

### 所选的题解
 - **作者：Ryo_Yamada（4星）**
    - **关键亮点**：思路清晰，通过统计偶数个数来分情况判断，代码简洁明了。
    - **个人心得**：提到WA2了一次，强调要找全可能性。
    ```cpp
    int r, g, b, w, cnt;
    int main() {
        int t;
        cin >> t;
        while(t--) {
            cnt = 0;
            scanf("%d%d%d%d", &r, &g, &b, &w);
            if(r % 2 == 0) cnt++;
            if(g % 2 == 0) cnt++;
            if(b % 2 == 0) cnt++;
            if(w % 2 == 0) cnt++;
            if(cnt >= 3) puts("Yes");
            else if(!r ||!g ||!b) puts("No");
            else {
                if(cnt == 2) puts("No");
                else puts("Yes");
            }
        }
        return 0;
    }
    ```
    - **核心实现思想**：统计四种球个数为偶数的个数 `cnt`，若 `cnt` 大于等于3则可以构成回文；若红绿蓝中有一个为0则不能构成回文；否则若 `cnt` 为2不能构成回文，其他情况可以构成回文。
 - **作者：_tommysun_（4星）**
    - **关键亮点**：从球总数的奇偶性出发，分别讨论构成回文的条件，代码逻辑清晰。
    ```cpp
    long long n,a,b,c,d;
    int main(){
        ios_base::sync_with_stdio(0); 
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>a>>b>>c>>d;
            while(a>0&&b>0&&c>0&&(a%2+b%2+c%2>1)){ 
                a--; b--; c--; d+=3; 
            }
            if(a%2+b%2+c%2+d%2<=1) cout<<"Yes"<<endl; 
            else cout<<"No"<<endl;
        }
        return 0;
    }
    ```
    - **核心实现思想**：通过循环操作，在可以操作且不满足回文条件时进行操作，最后判断操作后是否满足回文条件（即奇数个数小于等于1）。
 - **作者：Demoe（4星）**
    - **关键亮点**：简洁地指出每次操作改变四个数奇偶性，最多操作一次，直接根据奇偶个数判断。
    ```cpp
    ll a,b,c,d,x,cnt,T;
    int main(){
        rd(T);
        while(T--){
            rd(a);rd(b);rd(c);rd(d);
            cnt=(a&1)+(b&1)+(c&1)+(d&1);
            x=min(a,min(b,c));
            if(x==0){
                if(cnt>1) cout<<"No"<<endl;
                else cout<<"Yes"<<endl;
            }
            else{
                if(cnt==2) cout<<"No"<<endl;
                else cout<<"Yes"<<endl;
            }
        }
        return 0;
    }
    ```
    - **核心实现思想**：先统计初始的奇数个数 `cnt`，若有球数为0则直接根据 `cnt` 判断；否则若 `cnt` 不为2则可以构成回文。

### 最优关键思路或技巧
利用回文序列对球个数奇偶性的要求，结合操作对奇偶性的改变规律（操作两次奇偶性不变），通过统计奇数个数来判断能否构成回文。同时要注意球数为0时无法操作的特殊情况。

### 可拓展思路
此类题目可以拓展到更多颜色的球，或者改变操作方式，依然从奇偶性、操作对奇偶性的影响以及回文的条件等方面入手分析。

### 洛谷相似题目推荐
 - [P1146 硬币翻转](https://www.luogu.com.cn/problem/P1146)
 - [P1226 取余运算](https://www.luogu.com.cn/problem/P1226)
 - [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)

### 个人心得摘录与总结
Ryo_Yamada提到WA2了一次，强调做这类题要找全可能性，避免遗漏情况导致错误。这提醒在解决此类问题时，要全面细致地分析各种可能情况。 

---
处理用时：48.10秒