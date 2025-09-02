# 题目信息

# Mahmoud and Ehab and the binary string

## 题目描述

Mahmoud and Ehab are in the fourth stage now.

Dr. Evil has a hidden binary string of length $ n $ . He guarantees that there is at least one '0' symbol and at least one '1' symbol in it. Now he wants Mahmoud and Ehab to find a position of any '0' symbol and any '1' symbol. In order to do this, Mahmoud and Ehab can ask Dr. Evil up to $ 15 $ questions. They tell Dr. Evil some binary string of length $ n $ , and Dr. Evil tells the Hamming distance between these two strings. Hamming distance between 2 binary strings of the same length is the number of positions in which they have different symbols. You can find the definition of Hamming distance in the notes section below.

Help Mahmoud and Ehab find these two positions.

You will get Wrong Answer verdict if

- Your queries doesn't satisfy interaction protocol described below.
- You ask strictly more than $ 15 $ questions and your program terminated after exceeding queries limit. Please note, that you can do up to $ 15 $ ask queries and one answer query.
- Your final answer is not correct.

 You will get Idleness Limit Exceeded if you don't print anything or if you forget to flush the output, including for the final answer (more info about flushing output below).If you exceed the maximum number of queries, You should terminate with 0, In this case you'll get Wrong Answer, If you don't terminate you may receive any verdict because you'll be reading from a closed stream .

## 说明/提示

Hamming distance definition: [https://en.wikipedia.org/wiki/Hamming\_distance](https://en.wikipedia.org/wiki/Hamming_distance)

In the first test case the hidden binary string is 101, The first query is 000, so the Hamming distance is $ 2 $ . In the second query the hidden string is still 101 and query is 001, so the Hamming distance is $ 1 $ .

After some queries you find that symbol at position $ 2 $ is '0' and symbol at position $ 1 $ is '1', so you print "! 2 1".

## 样例 #1

### 输入

```
3
2
1
3
2
1
0```

### 输出

```
? 000
? 001
? 010
? 011
? 100
? 101
! 2 1```

# AI分析结果

### 题目重写
# Mahmoud和Ehab与二进制字符串

## 题目描述
Mahmoud和Ehab现在处于第四阶段。
邪恶博士有一个长度为$n$的隐藏二进制字符串。他保证其中至少有一个'0'符号和至少一个'1'符号。现在他希望Mahmoud和Ehab找到任意一个'0'符号和任意一个'1'符号的位置。为了做到这一点，Mahmoud和Ehab最多可以向邪恶博士询问15次。他们告诉邪恶博士一个长度为$n$的二进制字符串，邪恶博士会告诉他们这两个字符串之间的汉明距离。两个相同长度的二进制字符串之间的汉明距离是它们不同符号的位置数量。你可以在下面的注释部分找到汉明距离的定义。
帮助Mahmoud和Ehab找到这两个位置。
如果出现以下情况，你将得到错误答案的判定：
- 你的查询不满足下面描述的交互协议。
- 你询问的次数严格超过15次，并且你的程序在超过查询限制后终止。请注意，你最多可以进行15次询问和1次回答查询。
- 你的最终答案不正确。
如果你没有输出任何内容，或者忘记刷新输出（包括最终答案），你将得到空闲时间限制超出的判定（关于刷新输出的更多信息如下）。如果你超过了最大查询次数，你应该以0终止程序。在这种情况下，你将得到错误答案。如果你不终止，你可能会收到任何判定，因为你将从一个关闭的流中读取数据。

## 说明/提示
汉明距离定义：[https://en.wikipedia.org/wiki/Hamming\_distance](https://en.wikipedia.org/wiki/Hamming_distance)
在第一个测试用例中，隐藏的二进制字符串是101，第一个查询是000，所以汉明距离是2。在第二个查询中，隐藏字符串仍然是101，查询是001，所以汉明距离是1。
经过一些查询后，你发现位置2的符号是'0'，位置1的符号是'1'，所以你输出 "! 2 1"。

## 样例 #1
### 输入
```
3
2
1
3
2
1
0
```
### 输出
```
? 000
? 001
? 010
? 011
? 100
? 101
! 2 1
```

### 算法分类
二分

### 综合分析与结论
这几道题解的核心思路都是通过有限次数的询问，利用汉明距离的特性来确定字符串中'0'和'1'的位置。不同题解在具体实现方式上有所差异，有的采用随机化结合二分，有的直接利用二分查找，有的通过巧妙的询问顺序和区间判断来解决问题。

### 所选的题解
- **作者：dead_X (5星)**
    - **关键亮点**：思路简洁清晰，先通过两次询问确定第一位字符，再利用二分在剩余字符中查找另一个目标字符，代码实现简洁明了。
    - **重点代码核心实现思想**：先通过询问全0串和首位置为1其余为0的串确定第一位是0还是1，之后根据需要查找的字符，在剩余区间通过二分判断区间内是否全是不需要的字符，从而缩小查找范围。
    ```cpp
    signed main(){
        int n=read();
        printf("? ");
        for(int i=1; i<=n; i++) printf("0");
        puts(""),fflush(stdout);
        int p=read();
        printf("? 1");
        for(int i=1; i<n; i++) printf("0");
        puts(""),fflush(stdout);
        int q=read();
        int id0=-1,id1=-1; 
        if(p>q) 
        {
            id1=1;//we need 0
            int l=2,r=n;
            while(l<=r)
            {
                if(l==r) 
                {
                    id0=l;
                    break;
                }
                int mid=(l+r)>>1;
                printf("? ");
                for(int i=1; i<=n; i++) if(l<=i && i<=mid) printf("1"); else printf("0");
                puts(""),fflush(stdout);
                int res=read();
                if(p-res==mid-l+1) l=mid+1; else r=mid; 
            }
        }
        else
        {
            id0=1;//we need 1
            int l=2,r=n;
            while(l<=r)
            {
                if(l==r) 
                {
                    id1=l;
                    break;	
                }
                int mid=(l+r)>>1;
                printf("? ");
                for(int i=1; i<=n; i++) if(l<=i && i<=mid) printf("1"); else printf("0");
                puts(""),fflush(stdout);
                int res=read();
                if(res-p==mid-l+1) l=mid+1; else r=mid; 
            }
        }
        printf("! %d %d\n",id0,id1);
        fflush(stdout);
        return 0;
    }
    ```
- **作者：wmrqwq (4星)**
    - **关键亮点**：先通过两次询问确定一个目标字符的位置，再利用二分查找另一个目标字符的位置，逻辑清晰，代码注释详细。
    - **重点代码核心实现思想**：先通过询问全0串和首位置改变的串确定第一个目标字符位置，之后根据已确定的字符，通过构造特定字符串二分查找另一个目标字符位置。
    ```cpp
    void solve()
    {
        _clear();
        cin>>n;
        forl(i,1,n)
            S+='0';
        ll q1=ask(S);
        S[0]='1';
        ll q2=ask(S);
        if(q1>q2)
            ans1=1;
        else
            ans0=1;
        S="";
        forl(i,1,n)
            S+='1';
        ll q3=ask(S);
        if(!ans0)
        {
            ll L=1,R=n;
            while(L<R)
            {
                ll Mid=(L+R)/2;
                if(ask(f(Mid))==q3+Mid)
                    L=Mid+1;
                else
                    R=Mid; 
            }
            cout<<"! "<<L<<' '<<ans1<<endl;
        }
        else
        {
            ll L=1,R=n;
            while(L<R)
            {
                ll Mid=(L+R)/2;
                if(ask(f2(Mid))==q1+Mid)
                    L=Mid+1;
                else
                    R=Mid; 
            }
            cout<<"! "<<ans0<<' '<<L<<endl;		
        }
    }
    ```
- **作者：lytqwq (4星)**
    - **关键亮点**：通过特定的询问方式，结合区间判断和递归二分查找，逐步缩小查找范围找到目标位置。
    - **重点代码核心实现思想**：先通过询问全0串和首位置改变的串确定第一个目标字符位置，之后通过改变区间内字符询问并根据汉明距离变化判断目标字符所在区间，递归查找。
    ```cpp
    void findans(int l,int r,int flag,int bef){
        if(l==r){
            if(flag)ans1=l;
            else ans0=l;
            return ;
        }
        int mid=(l+r)>>1,now1;
        for(int i=l;i<=mid;i++){
            ask[i]='1'+'0'-ask[i];
        }
        cout<<"? "<<ask<<endl;
        cin>>now1;
        if(ask[l]-'0'==flag){
            if(now1-bef==mid-l+1)findans(mid+1,r,flag,now1);
            else findans(l,mid,flag,now1);
        }
        else{
            if(bef-now1==mid-l+1)findans(mid+1,r,flag,now1);
            else findans(l,mid,flag,now1);
        }
    }
    ```

### 最优关键思路或技巧
利用二分思想，通过巧妙构造询问字符串，根据汉明距离的变化来缩小查找'0'和'1'位置的范围，有效减少询问次数。

### 拓展思路
此类题目属于交互性问题，类似的题目通常需要利用有限的询问次数，结合特定的算法（如二分、贪心等）来获取所需信息。解题关键在于深入理解题目给定的交互规则，挖掘其中隐藏的信息变化规律，从而设计出高效的询问策略。

### 洛谷推荐题目
- [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)：基础的二分查找应用题目，帮助巩固二分查找的基本思路和实现。
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：通过二分查找解决最优解问题，与本题利用二分缩小范围的思路类似。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样是利用二分查找解决实际问题，锻炼二分查找在不同场景下的应用能力。 

---
处理用时：63.09秒