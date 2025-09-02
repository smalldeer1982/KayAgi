# [NWRRC 2013] Correcting Curiosity

## 题目描述

# [NWRRC2013] Correcting Curiosity


“好奇号”是探索火星上盖尔陨石坑的火星车。最近，它在火星土壤中发现了水存在的证据，这将使未来的火星登陆任务变得更加容易。$ $

“好奇号”可以用高达$32 Kbit/s$的速度与地球直接通信 ，但在地球和火星之间传输信号分别平均需要$14$秒和$6$秒。

`你刚刚看到一块石头并踩下了刹车，但你知道火星车已经经过那块石头了` -- 火星车司机Matt Heverly解释道。`所以我们需要规划路线，然后写下一个简单的命令列表：如向前移动一米，左转，拍照等等`.

有时你有必要对一些突发事件做出非常迅速的反应。例如，当相机看到了一些有趣的东西，那么你可能会想改变火星车的路线来拍摄的照片。为此，您需要发送一个形式为 $s/〈string〉/〈replacement〉/g$ . 这将替换所有出现的 $〈string〉,$ 从最左边的开始, 到 $〈replacement〉.$

更确切地说，如果A是非空字符串，而$B$是字符串, 则要将替换命令$s/A/B/g$应用于字符串$s$，执行以下操作：

在$S$中查找最左边出现的A，这样$S=$SL$+$A$+$SR。

如果没有A，请停止操作。$S$就是答案。

让$R$成为对SR应用$s/A/B/g$的结果。

那么答案是SL$+B+R$。

这就说明:

如果在$S$中有两个重叠的A，那么只替换最左边的一个。例如，将$`s/aba/c/g`$应用于`abababa`会产生`cbc`：在替换第一个`aba `之后，字符串将变为`cbaba `，在此之后只能替换最后一个出现的` aba `。

如果没有替换就使用先前替换的结果。例如，将$`s/a/ab/g`$应用于`a`产生`ab`，将$`s/s/a/ba/g`$应用于`a`产生`ba`。

命令越长，传输它所需的时间就越长。因此，需要你编写一个程序，找到最短的命令，将初始字符串转换为最终字符串。

## 说明/提示

时间限制: 2 s, 内存限制: 256 MB.

## 样例 #1

### 输入

```
move left, move right; move up
move left, move down, move up
```

### 输出

```
s/right;/down,/g
```

## 样例 #2

### 输入

```
If not found: move x; else move -x
If found: move x; else move -x
```

### 输出

```
s/ not//g
```

## 样例 #3

### 输入

```
abababa
cbc
```

### 输出

```
s/aba/c/g
```

# 题解

## 作者：stardust_Ray (赞：0)

简要题意：给你串 $A,B$，你要进行一次操作 $(S,T)$，将 $A$ 中出现的 $S$ 替换成 $T$，如果有两个重叠的 $S$，那么只替换最左边的一个。

首先 $S$ 和 $T$ 分别是 $A,B$ 的子串。观察到如果把 $A$ 中出现的 $S$ 标成特殊字符，$B$ 中出现的 $T$ 标成同样的字符，那么剩下的两个串必然相等。可以证明当 $T\not =\empty$ 的时候这是充要条件。所以我们考虑如何计算 $f_{l,r}$ 表示对 $A$ 中的 $S=A_{l,r}$ 依次替换成特殊字符后的哈希值。

我们枚举 $[l,r]$ 的长度，先对每个 $[l,r]$ 计算出开头在 $r$ 后面的它第一次出现的地方 $pos$，这个可以从后往前扫一遍得到。然后令 $g_{l,r} $ 表示对 $A_{l,|A|}$ 中的 $A_{l,r}$ 替换成特殊字符后的结果，这个是可以直接从 $g_{pos,pos+r-l}$ 转移而来的。之后稍微处理一下就可以得到 $f$。同理我们对 $B$ 也求一遍。如果有 $l_1,r_1,l_2,r_2$ 使得 $f_{A,l_1,r_1}=f_{B,l_2,r_2}$，那么说明 $S=A_{l1,r1},T=B_{l2,r2}$ 是一组合法的解。输出总长度最小的即可。

但我们仔细阅读题目，发现 $T$ 可以是空串，所以需要求 $h_{l,r}$ 表示把 $A$ 中的 $A_{[l,r]}$ 删掉而不是替换成特殊字符的哈希值，和 $B$ 串的哈希值比较即可。

如果用 map 实现，时间复杂度 $O(n^2\log n)$。代码常数过大，洛谷上要跑 $1.7s$。

```c++
#define LJY main
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=2005;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int TMP=rnd();
const int B=((rnd()>>11)<<7)|(rnd()&127)|3; // 随机 base，自然溢出
ull pw[N];string S,T;
struct Hsh{ // 哈希值
  int len;ull v;
  Hsh(){len=v=0;}
  Hsh(char x){len=1;v=x;}
  Hsh(int _l,ull _v):len(_l),v(_v){}
  bool operator<(const Hsh b)const{
    if(len!=b.len) return len<b.len;
    return v<b.v;
  }
}ss[N],st[N],fs[N][N],ft[N][N];
inline Hsh operator+(Hsh a,Hsh b){
  return {a.len+b.len,a.v*pw[b.len]+b.v};}
inline Hsh hsh1(int l,int r){
  if(l>r) return Hsh();
  return {r-l+1,ss[r].v-ss[l-1].v*pw[r-l+1]};}
inline Hsh hsh2(int l,int r){
  if(l>r) return Hsh();
  return {r-l+1,st[r].v-st[l-1].v*pw[r-l+1]};}
unordered_map<ull,int>mp;
map<Hsh,pair<int,int> >Mp;
void clear(unordered_map<ull,int>&x){
	unordered_map<ull,int>y;x.swap(y);}
signed LJY(){
  pw[0]=1;For(i,1,N-1) pw[i]=pw[i-1]*B;
  ios::sync_with_stdio(0);cin.tie(0);
  getline(cin,S);getline(cin,T);
  int n=S.size(),m=T.size();S=' '+S;T=' '+T;
  For(i,1,n) ss[i]=ss[i-1]+S[i];
  For(i,1,m) st[i]=st[i-1]+T[i];
  int ans=n+m;pair<int,int>U,V;
  U={1,n};V={1,m};
  
  For(len,1,n){
    For(l,1,n-len+1) fs[l][l+len-1]='*'+hsh1(l+len,n);
    clear(mp);
    ForDown(l,n-len+1,1){
      mp[hsh1(l,l+len-1).v]=l;Hsh tmp=hsh1(l-len,l-1);
      if(l-len>0&&mp.count(tmp.v)){
        int pos=mp[tmp.v]; // 用 unordered_map 找到下一个出现的位置，转移 g 
        fs[l-len][l-1]='*'+hsh1(l,pos-1)+fs[pos][pos+len-1]; 
      }
    }
    for(auto [_,x] within mp){ // 还留在 map 里的是可以成为最终哈希值的
			int r=x+len-1;
      fs[x][r]=hsh1(1,x-1)+fs[x][r]; // 加上一段前缀，计算出 f
      if(!Mp.count(fs[x][r])) Mp[fs[x][r]]={x,len}; // 放到 map 中便于后面查询
    }
  }
  For(len,1,m){
    For(l,1,m-len+1) ft[l][l+len-1]='*'+hsh2(l+len,m);
    clear(mp);
    ForDown(l,m-len+1,1){
      mp[hsh2(l,l+len-1).v]=l;Hsh tmp=hsh2(l-len,l-1);
      if(l-len>0&&mp.count(tmp.v)){
        int pos=mp[tmp.v];
        ft[l-len][l-1]='*'+hsh2(l,pos-1)+ft[pos][pos+len-1]; //同上
      }
    }for(auto [_,l] within mp){
			int r=l+len-1;
      ft[l][r]=hsh2(1,l-1)+ft[l][r]; // 同上
      if(Mp.count(ft[l][r])){
        auto [L,ln]=Mp[ft[l][r]];
        int res=ln+r-l+1; // 查询答案
        if(res<ans) ans=res,U={L,L+ln-1},V={l,r};
      }
    }
  }
  // -- T 非空的情况 ⬆
  // -- T 为空串的情况 ⬇
  For(len,1,n){
    For(l,1,n-len+1) fs[l][l+len-1]=hsh1(l+len,n);
    clear(mp);
    ForDown(l,n-len+1,1){
      mp[hsh1(l,l+len-1).v]=l;
      if(l-len>0&&mp.count(hsh1(l-len,l-1).v)){
        int pos=mp[hsh1(l-len,l-1).v];
        fs[l-len][l-1]=hsh1(l,pos-1)+fs[pos][pos+len-1]; // 不用加特殊字符
      }
    }
    for(auto [_,x] within mp){
			int r=x+len-1;
      fs[x][r]=hsh1(1,x-1)+fs[x][r];
      if(fs[x][r].len==m&&fs[x][r].v==st[m].v){ // 和 B 串比较
        if(ans>len) ans=len,U={x,r},V={1,0};
      }
    }
  }
  printf("s/");
  For(i,U.first,U.second) putchar(S[i]);putchar('/');
  For(i,V.first,V.second) putchar(T[i]);putchar('/');putchar('g');
  return 0;
}
```

不知道我是怎么把小清新题写成【数据删除】的。

---

