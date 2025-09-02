# 题目信息

# 元素の系統名

## 题目描述

[problemUrl]: https://atcoder.jp/contests/qupc2014/tasks/qupc2014_b

原子番号を与える．それに対応する「元素の系統名（げんそのけいとうめい）」を出力せよ． 「元素の系統名」とは、原子番号の各位を、以下の表にしたがって綴ったものである。 また、一文字目は大文字で表記する。 あなたの仕事は元素番号が117番以降の3桁の元素の名前をつけることである。

数字綴り（1の位以外）綴り（1の位）0nilnilium1ununium2bibium $ * $3tritrium $ * $4quadquadium5pentpentium6hexhexium7septseptium8octoctium9enn $ * $ennium $ * $印が付いている表記について 注意が必要である "bi"または"tri"が"ium"と連結する場合は連続する"ii"は"i"と表記する。"enn"が"nil"または"nilium"と連結する場合は連続する"（e）nn"は"（e）n"と表記する 入力は以下の形式で与えられる。 > $ N $

 Nは原子番号である。 入力中は各変数はすべて整数である。また、以下の制約を満たす。 - $ 117≦N≦999 $
 
 元素の系統名（げんそのけいとうめい）を一行で出力してください ```
<pre class="prettyprint linenums">
145
```

 ```
<pre class="prettyprint linenums">
Unquadpentium
```


```
<pre class="prettyprint linenums">
902
```

 ```
<pre class="prettyprint linenums">
Ennilbium
```

# AI分析结果

【题目内容翻译】
# 元素的系统名

## 题目描述

给定一个原子序数，输出其对应的“元素的系统名”。元素的系统名是根据原子序数的每一位数字，按照以下表格中的规则拼写而成的。此外，首字母需要大写。你的任务是为117号及以上的三位数元素命名。

数字 | 拼写（非个位） | 拼写（个位）
--- | --- | ---
0 | nil | nilium
1 | un | unium
2 | bi | bium
3 | tri | trium
4 | quad | quadium
5 | pent | pentium
6 | hex | hexium
7 | sept | septium
8 | oct | octium
9 | enn | ennium

注意：当“bi”或“tri”与“ium”连接时，连续的“ii”应简化为“i”。当“enn”与“nil”或“nilium”连接时，连续的“nn”应简化为“n”。

输入格式：
> $ N $

其中，$ N $ 是原子序数。输入中的所有变量均为整数，且满足以下约束：
- $ 117 \leq N \leq 999 $

输出格式：
输出元素的系统名，占一行。

【算法分类】
模拟

【题解分析与结论】
本题的核心是通过模拟的方式，根据原子序数的每一位数字，按照给定的规则拼写出元素的系统名。难点在于处理特殊情况，如“bi”或“tri”与“ium”连接时的简化，以及“enn”与“nil”连接时的简化。

【评分较高的题解】
1. **作者：死神审判 (赞：5)**
   - **星级：4.5**
   - **关键亮点**：使用了字符串数组打表，简化了代码逻辑，清晰处理了特殊情况。
   - **个人心得**：作者提到“有许多的坑”，表明在实现过程中遇到了不少细节问题，最终通过特判解决了这些问题。
   - **核心代码**：
     ```cpp
     string a[10]={"Nil","Un","Bi","Tri","Quad","Pent","Hex","Sept","Oct","Enn"};
     string b[10]={"nil","un","bi","tri","quad","pent","hex","sept","oct","enn"};
     int main(){
         string s;
         cin>>s;
         cout<<a[s[0]-'0'];
         if(s[1]=='0'&&s[0]!='9')cout<<"nil";
         else if(s[1]=='0'&&s[0]=='9')cout<<"il";
         else cout<<b[s[1]-'0'];
         if(s[2]=='0'&&s[1]!='9')cout<<"nil";
         else if(s[2]=='0'&&s[1]=='9')cout<<"il";
         else cout<<b[s[2]-'0'];
         if(s[2]=='2'||s[2]=='3')cout<<"um\n";
         else cout<<"ium\n";
         return 0;
     }
     ```

2. **作者：infinities (赞：3)**
   - **星级：4**
   - **关键亮点**：通过暴力枚举的方式处理每一位数字，代码简洁明了，易于理解。
   - **个人心得**：作者提到“没好好看题之前，我打出了这个代码，信心满满地提交（非正解，别忙着抄）”，表明在初次实现时忽略了题目中的细节，最终通过仔细审题解决了问题。
   - **核心代码**：
     ```cpp
     int main(){
         int a;
         cin>>a;
         if(a/100==1)cout<<"Un";
         else if(a/100==2)cout<<"Bi";
         // 省略部分代码
         if(a%10==2||a%10==3)cout<<"um\n";
         else cout<<"ium\n";
         return 0;
     }
     ```

3. **作者：Keep_RAD (赞：0)**
   - **星级：4**
   - **关键亮点**：通过逐个字符处理的方式，清晰处理了特殊情况，代码结构清晰。
   - **核心代码**：
     ```cpp
     int main(){
         int n;
         cin>>n;
         int aa=n/100,bb=(n/10)%10,cc=n%10;
         cout<<a[aa];
         if(aa==9&&bb==0)cout<<"il";
         else cout<<a[bb];
         if(bb==9&&cc==0)cout<<"il";
         else cout<<a[cc];
         if(cc==2||cc==3)cout<<"um\n";
         else cout<<"ium\n";
         return 0;
     }
     ```

【最优关键思路或技巧】
1. **打表法**：通过字符串数组存储每个数字对应的拼写，简化了代码逻辑，减少了重复代码。
2. **特判处理**：针对特殊情况（如“bi”或“tri”与“ium”连接时的简化），通过特判进行处理，确保输出正确。
3. **逐个字符处理**：通过逐个字符处理的方式，清晰处理了每一位数字的拼写，代码结构清晰。

【可拓展之处】
本题的模拟思路可以拓展到其他类似的拼写问题，如根据数字拼写日期、时间等。类似的题目可以通过打表和特判的方式简化代码逻辑。

【推荐题目】
1. [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

---
处理用时：34.15秒