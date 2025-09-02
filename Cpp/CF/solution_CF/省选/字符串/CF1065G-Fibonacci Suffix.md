# Fibonacci Suffix

## 题目描述

我们再次定义斐波那契字符串序列：

$F(0) = $ 0，$F(1) = $ 1，$F(i) = F(i - 2) + F(i - 1)$，其中加号表示两个字符串的连接。

我们将字符串 $F(i)$ 的所有后缀按字典序排序后得到的序列记为 $A(F(i))$。例如，$F(4)$ 为 01101，$A(F(4))$ 为以下序列：01，01101，1，101，1101。该序列中的元素从 $1$ 开始编号。

你的任务是输出 $A(F(n))$ 中第 $k$ 个元素的前 $m$ 个字符。如果该后缀长度小于 $m$，则输出整个后缀。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5 3
```

### 输出

```
110
```

## 样例 #2

### 输入

```
4 3 3
```

### 输出

```
1
```

# 题解

## 作者：是个汉子 (赞：8)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1065G)	[CF传送门](http://codeforces.com/problemset/problem/1065/G)

~~弄这个题，弄了一天半，才弄完。~~

### Solution

首先暴力的想法是直接合并串，再将 $F(n)$ 的所有后缀进行字典序的排序，最后将前 $\min(m,|suf_k|)$ 位输出。

但是发现：

1. 存不下这么长的后缀，我们发现 $F$ 的长度就是斐波那契数列，那么当 $n$ 稍微大一点的时候，长度是会超过 $10^{10}$ 的。例如： $F(50)$ 的长度是 $20365011074$ 。

2. 存不了这么多的后缀。

但是~~因为懒~~为了更好的体现部分分，我们选择将前 $15$ 个串预处理出来，当 $n\leq 15$ 时，可以暴力找。

因为 $F(12)$ 的长度就已经超过 $200$ 了，即 $m$ 的上界，所以在处理更大更多的情况时就可以不用特判小的情况了。

---

现在考虑正解。

因为这个串只由 $0,1$ 组成，而且 $m\leq 200$ ，所以可以判断前 $m$ 位上分别填什么。

那么现在就要找到一种方法：可以找出**如果第 $i$ 位是 $1$ ，有多少比已经填出的前 $i-1$ 位 $ans$ 的字典序小的后缀**。（以下 ‘已经填出的前 $i-1$ 位 $ans$ ’ 均用 ‘ $ans$ ’ 代替）

设 $f_i$ 表示 $F(i)$ 的后缀中有多少小于 $ans$，那么转移就是：
$$
f_i=f_{i-1}+f_{i-2}+mg_{i-2,i-1}
$$
其中 $mg_{i,j}$ 表示将 $F(i)$ 和 $F(j)$ 拼起来所增加的比 $ans$ 小的后缀个数。

但是 $mg$ 也不能暴力求，因为长度还是太大了，怎么办呢？

我们发现，对于 $mg_{i-2,i-1}$ ，它表示的的其实是 $F(i-2)$ 长为 $|ans|-1$ 的后缀到 $F(i-1)$ 长为 $|ans|-1$ 的前缀合并所增加的，别的在 $f_{i-1},f_{i-2}$ 中就已经算到了。

等等， $F(i-2)$ 的这个后缀是哪来的，不就是 $F(i-3)$ 的后缀吗！！！

 $F(i-1)$ 的那个前缀同理，那么我们就可以这么递归到 $F(15)$ 和 $F(14)$ 。

啥？为什么是 $F(15)$ ？因为我在最上面的时候，把前 $15$ 个串处理出来了(oﾟvﾟ)ノ

因为只会用到 $F(15),F(14)$ 的前缀和后缀，所以可以将 $mg_{14,15}$  表示为 $mg_{d_{14},h_{15}}$ ，在转移的时候也转移 $d,h$ 即可： $d_i=d_{i-2},h_i=h_{i-1},d_{14}=h_{14}=0,d_{15}=h_{15}=1$ 。

那么将 $f_{15},f_{14},mg_{0/1,0/1}$ 预处理即可。

蛤？怎么处理？一位一位暴力配对呗

---

到此为止，这个题就完了。o(\*￣▽￣*)o

注意：当 $n>15$ 时，输出的答案的长度可能还是 $<m$ 的，因为在确定了某些位置后， $k=0$ ，那么现在这个确定了某些位置的答案其实已经是最后答案。（你品，你细品）

剩下细节看代码吧

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=210;
int n,m;
ll k,f[N],d[N],h[N],mg[2][2];
string pre[2],nxt[2],str[17],suf[N*10],ans;

inline bool cmp(string a,string b){
    for(int i=0;i<min(a.length(),b.length());i++){
        if(a[i]==b[i]) continue;
        if(a[i]<b[i]) return 1;
        else return 0;
    }
    return a.length()<b.length();
}

int count(string a){    //数出来有几个比现在的ans小的
    int res=0;
    for(int i=0;i<a.length();i++){
        if(i+ans.length()-1>=a.length()) break;
        bool flag=1;
        for(int j=0;j<ans.length();j++)
            if(a[i+j]!=ans[j]) flag=0;
        res+=flag;
    }
    return res;
}

ll solve(){
    int len=ans.length();
    pre[0].clear();pre[1].clear();nxt[0].clear();nxt[1].clear();    //记得清零
    d[14]=h[14]=0; d[15]=h[15]=1;   //转移f的时候用
    for(int i=0;i<len-1;i++) pre[0].push_back(str[14][i]),pre[1].push_back(str[15][i]);
    for(int i=1;i<=len-1;i++) nxt[0].push_back(str[14][str[14].length()-len+i]);
    for(int i=1;i<=len-1;i++) nxt[1].push_back(str[15][str[15].length()-len+i]);
    //将第14,15个串对于ans的前缀和后缀处理出来
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            mg[j][i]=count(nxt[j]+pre[i]);  //合并时多出的后缀情况
    f[14]=count(str[14]); f[15]=count(str[15]);
    for(int i=16;i<=n;i++){
        h[i]=h[i-1];
        d[i]=d[i-2];
        f[i]=f[i-1]+f[i-2];
        f[i]+=mg[d[i]][h[i]];
        if(f[i]>1e18) return f[i];  //因为k小于1e18,所以可以直接判断
    }
    //大力转移
    return f[n];
}

int main(){
    scanf("%d%lld%d",&n,&k,&m);
    str[0]="0"; str[1]="1";
    for(int i=2;i<=15;i++) str[i]=str[i-2]+str[i-1];    //将前15个串预处理出来
    if(n<=15){  //暴力部分
        for(int i=0;i<str[n].length();i++)
            for(int j=i;j<str[n].length();j++)
                suf[i+1].push_back(str[n][j]);
        sort(suf+1,suf+str[n].length()+1,cmp);
        for(int i=0;i<min(m,(int)suf[k].length());i++) printf("%c",suf[k][i]);
        return 0;
    }
    for(int i=1;i<=m;i++){  //按位考虑
        ans.push_back('0');
        ll z=solve();       //判断现在这几位ans情况下，有多少比ans小
        if(z<k){
            k-=z;           //减去小于的
            ans.pop_back(); ans.push_back('1');//将这一位改为1
        }
        if(k==0){   //满足就直接输出,可能小于m位
            for(int i=0;i<ans.length();i++) printf("%c",ans[i]);
            return 0;
        }
    }
    for(int i=0;i<ans.length();i++)
        printf("%c",ans[i]);
    return 0;
}
```



---

