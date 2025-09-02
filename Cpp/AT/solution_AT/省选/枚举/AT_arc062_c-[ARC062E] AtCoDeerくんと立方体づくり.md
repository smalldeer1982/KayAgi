# [ARC062E] AtCoDeerくんと立方体づくり

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc062/tasks/arc062_c

シカのAtCoDeerくんは正方形のタイルを $ N $ 枚持っています。 各正方形の片面には $ 1～N $ の数が書いてあって、正方形の各頂点にはそれぞれ色が塗られています。色は $ 0～999 $の整数で表され、 $ i $ と書かれた正方形に塗られている色は、数の書かれている方向から見て左上、右上、右下、左下 の順に、 $ C_{i,0},C_{i,1},C_{i,2},C_{i,3} $ で与えられます(図$ 1 $を参照)。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc062_c/453abe518ff079ba7f47234605f07932e49bd429.png)図$ 1 $: タイルの色と入力の対応

 

AtCoDeerくんはこれらのタイルを$ 6 $枚組み合わせて次のような条件を満たす立方体を作ろうと考えました。

- 数の書いてある面が外側を向いている
- 立方体の各頂点に対し、そこに集まる正方形の頂点は$ 3 $つあるが、それらには全て同じ色が塗られている

AtCoDeerくんのために条件を満たす立方体が何通りあるか求めてください。ただし、正方形には数が書いてあるので、色の構成が同じだとしても使ったタイルが異なったり、使ったタイルの向き($ 90° $回転により$ 4 $通り考えられる)が異なるものは異なる立方体とみなします。 ただし、3次元空間で回転させることで使ったタイルの向きまで完全に一致するものは同じ立方体とみなします。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc062_c/e6a4d84ae97edb54b095e308a0392c4c47ac8209.png)図$ 2 $: 4方向のタイルの向き

## 说明/提示

### 制約

- $ 6≦N≦400 $
- $ 0≦C_{i,j}≦999\ (1≦i≦N\ ,\ 0≦j≦3) $

### Sample Explanation 1

下図のような立方体が作れます。 !\[\](https://atcoder.jp/img/arc062/094fbca5395bfaaea28c98c51230693b.png)

## 样例 #1

### 输入

```
6
0 1 2 3
0 4 6 1
1 6 7 2
2 7 5 3
6 4 5 7
4 0 3 5```

### 输出

```
1```

## 样例 #2

### 输入

```
8
0 0 0 0
0 0 1 1
0 1 0 1
0 1 1 0
1 0 0 1
1 0 1 0
1 1 0 0
1 1 1 1```

### 输出

```
144```

## 样例 #3

### 输入

```
6
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0```

### 输出

```
122880```

# 题解

## 作者：Z_Healer (赞：11)

前言：现有的两篇题解本蒟蒻有点难懂，在[ezoiHQM](https://www.luogu.com.cn/user/49097)大佬的基础上进行补充，希望能帮助我这样的蒟蒻。如有错误，请指出。

[AT2142 [ARC062C]](https://www.luogu.com.cn/problem/AT2142)

## 题意

给你$n$个正方形，每个正方形的中央都写着自己的编号$i$，四个角上各有一种颜色$c_{i,0},c_{i,1},c_{i,2},c_{i,3}$（左上、右上、右下、左下）。

选不同的$6$个正方形拼成一个**本质不同的合法**的立方体。立方体每个**顶点**处的三块颜色都相同，且每个正方形写着数的一面都朝外才是合法的。（注意，正方形是可以**旋转**的)。

本质相同的正方体：如果以某种方式旋转一个正方体后，两个正方体对应面上的数字和方向都相同。

求组成本质不同的合法的立方体的方案数。

## 分析


首先，我们来讨论一下$c_i$都相等的情况，也就是可以不用管顶点的颜色相同，这样可以随意选旋转过后的正方形。

方案数：

$$\dfrac{n(n-1)*4*A_{n-2}^4*4^4}{6}$$

$n:$枚举上面的正方形，$n-1:$枚举下面的正方形，$4:$下面的正方形旋转4下，$A_{n-2}^4:$枚举4个侧面(有顺序)，$4^4:$每个旋转4下，$\dfrac{1}{6}:$去重。



------------


从这个特殊情况我们可以知道，只要确定上下两个面，8个顶点的颜色就确定了，然后只要统计4个侧面满足情况的个数。

那么我们枚举两个对⾯及⽅向，那么剩下$n-2$个⾯可以在满⾜条件的中任意选。

把每个正方形四个⻆上的颜⾊哈希⼀下，然后存到$map$⾥，每次算的时候查⼀下即可。

需要注意⼀些细节避免算重，具体实现看代码。

## code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
inline int read(){
	int w=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch<='9'&&ch>='0'){
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w;
}
int n,c[410][4],tmp[5];
LL h[410],side[5],ans;
map<LL,int> cnt;
inline LL Hash(int a[]){//算每个正方形的hash
	LL sum=0;
	for(int i=0;i<4;i++)//因为颜色数<=999<2^10
		sum|=(LL)a[i]<<(i*10ll);//所以二进制下左移i*10位就可以避免重复
	return sum;//记得要强转long long
}
inline void change(LL x,int d){//修改出现次数，
	for(int i=0;i<4;i++){//正方形旋转
		cnt[x]+=d;
		x=(x>>10ll)|((x&1023ll)<<30ll);
        //取出3,2,1颜色的hash，取出0颜色的hash并放到前面。
	}
/*eg:
0 1     1 2     2 3     3 0
    -->     -->     -->
3 2     0 3     1 0     2 1

3210-->0321-->1032-->2103
*/
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++)
			c[i][j]=read();
		h[i]=Hash(c[i]);//求hash
		change(h[i],1);//出现次数+1
	}
	for(int i=1;i<=n-5;i++){//枚举上面
		change(h[i],-1);//去重，避免枚举侧面时重复统计
		for(int j=i+1;j<=n;j++){//枚举下面
			change(h[j],-1);//同上
			for(int p=0;p<4;p++){//旋转下面
				LL s=1;
				for(int q=0;q<4;q++){//枚举侧面：正->左->后->右面
					tmp[0]=c[i][3-q];//正方形4个颜色由上下面正方形的那个角的颜色确定
					tmp[1]=c[i][(6-q)%4];//建议结合样例一好好看看
					tmp[2]=c[j][(3+q+p)%4];//下面要旋转
					tmp[3]=c[j][(2+q+p)%4];
					side[q]=Hash(tmp);//对满足颜色凑出来的正方形求hash
					if(cnt[side[q]]==0){//判断这个正方形是否存在
						s=0;
						break;//大量优化时间，否则会T
					}
				}
				if(!s) continue;
				for(int q=0;q<4;q++){
					s*=cnt[side[q]];//乘法原理
					change(side[q],-1);//去重
				}
				for(int q=0;q<4;q++)
					change(side[q],1);//加回来,下次统计要用
				ans+=s;//加法原理
			}
			change(h[j],1);//同上
		}
	}
	printf("%lld",ans);
	return 0;
}
```
附样例一组成合法立方体的图

![](https://cdn.luogu.com.cn/upload/image_hosting/o8n5fet1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

---

## 作者：Zhao_daodao (赞：5)

# [ARC062E] AtCoDeerくんと立方体づくり

### description

给你 $n$ 块瓷砖，每一块的四个角上各有一个颜色，其中一面上有编号。

6 块瓷砖可以组成一个正方体，求合法正方体的数量。

- 正方体上一共 $8$ 个点，每一个点有三种颜色。方案合法当且仅当 **对于每一个点，这三种颜色都相同**。
- 如果方案 A 的正方体在空间中仅仅旋转能够变成方案 B，那么这两种方案相同。
- 对于一块瓷砖，编号的方向不同但是颜色相同，这两种方案不同。

### solution

首先，一块瓷砖能够确定四个角的颜色，那么两块瓷砖就能够完全确定一个正方体的染色方案。

所以，不妨先枚举一个正方体的上、下两面。因为空间中能够旋转，所以只需要考虑下面对于上面转了几个直角。

同时，因为可以整个倒转，所以钦定上面瓷砖的编号比下面瓷砖的编号小。

这样枚举时间复杂度为 $O(n^2)$。

---

在确定了每一个角的颜色之后，考虑剩下四个面的方案数。

发现直接算会有若干容斥，非常烦躁。

但是，**瓷砖之间的不同当且仅当旋转任意角度，两个瓷砖对应颜色至少有一个不同**。

换句话说，我们不需要考虑具体选出的是哪一块瓷砖，因为 **如果能够同时被选出，每一块瓷砖必然相同**。

所以，不用针对编号处理，而是考虑旋转后的方案数。

每一次选出一种瓷砖，将这种瓷砖的数量去掉一个就可以了，我们不关心选出的是哪一块。

直接记录就可以了。

---

具体的，加入每一块瓷砖的时候，将这个瓷砖的四个旋转角度的方案全部加 1。

每一次查询一种瓷砖的方案数，将这种瓷砖的四个旋转角度的方案全部减 1，随后一起加上就可以了。

统计的时候可以 map，把瓷砖的四角看作一个四位的 1000 进制数。

最后求出的答案是 3 倍的真正答案，因为一个正方体有三组对立的面，会被算三次。

总共的时间复杂度为 $O(n^2\log n)$，大概有4 倍常数，足以通过。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5e2+5;
unordered_map<int,int>mp;
int n,ans;
struct block{
    int a0,a1,a2,a3;
	block(int _0=0,int _1=0,int _2=0,int _3=0){a0=_0,a1=_1,a2=_2,a3=_3;}
	inline block turn(int x){
		if(x==0)return block(a0,a1,a2,a3);
		if(x==1)return block(a1,a2,a3,a0);
		if(x==2)return block(a2,a3,a0,a1);
		if(x==3)return block(a3,a0,a1,a2);
	}
	inline int hsh(){return a3+(a2+(a1+a0*1001)*1001)*1001;}
}a[MAXN];
inline void change(block now,int del){for(int j=0;j<=3;j++)mp[(now.turn(j)).hsh()]+=del;}
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a0>>a[i].a1>>a[i].a2>>a[i].a3;
		change(a[i],1);
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			for(int k=0;k<=3;k++){
				block fir=a[i],sec=a[j].turn(k);
				change(fir,-1),change(sec,-1);
				block c1(fir.a3,fir.a2,sec.a2,sec.a1);
				block c2(fir.a2,fir.a1,sec.a3,sec.a2);
				block c3(fir.a1,fir.a0,sec.a0,sec.a3);
				block c4(fir.a0,fir.a3,sec.a1,sec.a0);
				int cnt1=mp[c1.hsh()];change(c1,-1);
				int cnt2=mp[c2.hsh()];change(c2,-1);
				int cnt3=mp[c3.hsh()];change(c3,-1);
				int cnt4=mp[c4.hsh()];change(c4,-1);
				ans+=cnt1*cnt2*cnt3*cnt4;
				change(c1,1),change(c2,1),change(c3,1),change(c4,1);
				change(fir,1),change(sec,1);
			}
		}
	cout<<ans/3<<"\n";
}
```

---

## 作者：Krimson (赞：5)

**高质量好题**（指练习哈希  


------------

首先可以发现只要确定了一个立方体相对的两个面，就相当于确定了这个立方体的八个角上的颜色，也就是意味着能**确定这个立方体**，然后只要去统计剩下四个面有多少个可以拼接上去就好了      
  
但是，这道题难的地方~~其实不是很难~~就在于如何去统计  
首先能想到的肯定是要用到哈希  
然后我们考虑到这样一个瓷砖  $C_1,C_2,C_3,C_4$,它和$C_2,C_3,C_4,C_1$...之类都是属于同一种瓷砖，统计的时候应该把它们归为一种  
同时，如果出现了旋转了之后颜色跟原来一样的情况(比如{1,1,1,1})，那么应该记录一下，到时候在拼接的时候它的贡献应该是要乘以它有多少种旋转之后跟原来一样的情况(如上面给的{1,1,1,1}就应该有四种旋转之后颜色一样)  
于是考虑把每一块瓷砖用一个长度为8的数组存储下来$C_1,C_2,C_3,C_4,C_1,C_2,C_3,C_4$，再分别从第1,2,3,4往后4个哈希一遍   
这样还可以根据得到的四个哈希值来判断一下有多少种旋转之后一样的情况  

最后再把得到的四个哈希值给"捆绑在一起"(显然有很多高妙的做法)，这里我选择排序之后再哈希一遍，得到的就是最后的哈希值$va[i]$  
以下是笔者的代码  
```cpp
ll zz[4];
ll getHash(int x){//没有必要双哈，但是保险一点还是好的
    ll ans=0;
    map<ll,int> chk;
    chk.clear();
    for(ri i=0;i<4;++i){
        ll nowI=0;
        ll nowII=0;
        for(ri j=0;j<4;++j){
            nowI=(nowI*has+c[x][i+j]*j)%mod;
            nowII=(nowII*Has+c[x][i+j]*j)%Mod;            
        }
        nowI=(nowI+nowII)%Mod;
        chk[nowI]++;
        siz[x]=max(siz[x],chk[nowI]);
        zz[i]=nowI;
    }
    sort(zz,zz+4);
    for(ri i=0;i<4;++i) ans=(ans*has+zz[i])%Mod;
    return ans;
}
```
统计完之后只要照着一开始说的方法统计以下方案就好了  
这里有一个小技巧可以防止重复计算，每选择一个瓷砖就先把它"扔掉"，等统计完之后再把它"捡"回来  


------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
/*
先考虑一下怎么判断本质不同的立方体的个数  
用四个角跑一次哈希，再a+b+c+d%mod
*/
// #define node pair<int,int>
const int MAXN=1000;
const ll mod=19260817,Mod=1e9+7;
const ll has=1009,Has=131;
ll c[MAXN][8];
ll siz[MAXN];
map<ll,int> block,which;
ll zz[4];
ll getHash(int x){//没有必要双哈，但是保险一点还是好的
    ll ans=0;
    map<ll,int> chk;
    chk.clear();
    for(ri i=0;i<4;++i){
        ll nowI=0;
        ll nowII=0;
        for(ri j=0;j<4;++j){
            nowI=(nowI*has+c[x][i+j]*j)%mod;
            nowII=(nowII*Has+c[x][i+j]*j)%Mod;            
        }
        nowI=(nowI+nowII)%Mod;
        chk[nowI]++;
        siz[x]=max(siz[x],chk[nowI]);
        zz[i]=nowI;
    }
    sort(zz,zz+4);
    for(ri i=0;i<4;++i) ans=(ans*has+zz[i])%Mod;
    return ans;
}
int n;  
ll id[MAXN],cnt;
ll va[MAXN];
ll use[2][4];
ll ans;
int main(){
    // freopen("rand.in","r",stdin);
    // freopen("1.out","w",stdout);
    n=read();
    for(ri i=1;i<=n;++i){
        for(ri j=0;j<4;++j){
            c[i][j]=c[i][j+4]=read();
        }
        ll val=getHash(i);
        va[i]=val;
        if(!block[val]){
            which[val]=i;//选一个代表元素  
        }
        ++block[val];
    }
    //万一旋转之后还是能拼上怎么办呢？
    //用siz[i]来表示有多少种本质不同的选法
    for(ri i=1;i<=n;++i){//只会去选取比i小的元素,因为如果存在某个元素比i小，那么它在前面的时候一定被枚举到过,所以只需要把所有出现过的元素delete掉就好了
        block[va[i]]--;
        for(ri j=i+1;j<=n;++j){
            block[va[j]]--;
            for (ri O=0;O<4;++O){
                ll now=1;
                for(ri z=0;z<4;++z){
                    use[0][z]=c[i][z+O];
                    use[1][z]=c[j][z];
                }
                c[n+1][0]=c[n+1][4]=use[0][0];
                c[n+1][1]=c[n+1][5]=use[1][1];
                c[n+1][2]=c[n+1][6]=use[1][0];
                c[n+1][3]=c[n+1][7]=use[0][1];
                ll ha1=getHash(n+1);
                now*=siz[which[ha1]]*block[ha1]%mod;
                block[ha1]--;
                c[n+2][0]=c[n+2][4]=use[0][1];
                c[n+2][1]=c[n+2][5]=use[1][0];
                c[n+2][2]=c[n+2][6]=use[1][3];
                c[n+2][3]=c[n+2][7]=use[0][2];
                ll ha2=getHash(n+2);
                now*=siz[which[ha2]]*block[ha2]%mod;
                block[ha2]--;
                c[n+3][0]=c[n+3][4]=use[0][2];
                c[n+3][1]=c[n+3][5]=use[1][3];
                c[n+3][2]=c[n+3][6]=use[1][2];
                c[n+3][3]=c[n+3][7]=use[0][3];
                ll ha3=getHash(n+3);
                now*=siz[which[ha3]]*block[ha3]%mod;
                block[ha3]--;
                c[n+4][0]=c[n+4][4]=use[0][3];
                c[n+4][1]=c[n+4][5]=use[1][2];
                c[n+4][2]=c[n+4][6]=use[1][1];
                c[n+4][3]=c[n+4][7]=use[0][0];
                ll ha4=getHash(n+4);
                now*=siz[which[ha4]]*block[ha4]%mod;
                block[ha4]--;
                if(now>0) ans+=now;
                block[ha1]++;
                block[ha2]++;
                block[ha3]++;
                block[ha4]++;
                if(!block[ha1]) block.erase(ha1);
                if(!block[ha2]) block.erase(ha2);
                if(!block[ha3]) block.erase(ha3);
                if(!block[ha4]) block.erase(ha4);                
                if(!which[ha1]) which.erase(ha1);
                if(!which[ha2]) which.erase(ha2);
                if(!which[ha3]) which.erase(ha3);
                if(!which[ha4]) which.erase(ha4);

            }
            block[va[j]]++;
        }
    }
    print(ans);
    return 0;
}
```


---

## 作者：ezoiHQM (赞：5)

这道题真的就是暴力......	
首先我们会发现，只	要确定立方体的两个对面，就可以确定这一整个立方体
然后我们可以将每一个瓷砖旋转后的每一种颜色哈希后存进一个map里面，暴力枚举两个对面，然后利用map统计一下答案就好了。具体怎么统计不难理解，如果不会就看看代码吧:
```cpp
#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef long long ll;
int n;
ll ans,c[410][4],h[410],v[4],tmp[4];
unordered_map<ll,int>mp;
void upd(ll x,int d){
	for(int i=0;i<4;i++,x=((x&1023ll)<<30ll)|(x>>10ll))
		mp[x]+=d;
	return;
}
ll Hash(ll *a){
	ll ret=0;
	for(int i=0;i<4;i++)
		ret|=(a[i]<<(i*10ll));
	return ret;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",c[i],c[i]+1,c[i]+2,c[i]+3);
		h[i]=Hash(c[i]);
		upd(h[i],1);
	}
	for(int i=1;i<=n-5;i++){
		upd(h[i],-1);
		for(int j=i+1;j<=n;j++){
			upd(h[j],-1);
			for(int k=0;k<4;k++){
				ll res=1;
				for(int l=0;l<4;l++){
					ll tmp[]={c[i][(l+1)&3],c[i][l],c[j][(3-l+k)&3],c[j][(6-l+k)&3]};
					v[l]=Hash(tmp);
					if(!mp.count(v[l]))
						goto to;
				}
				for(int l=0;l<4;l++){
					res*=mp[v[l]];
					upd(v[l],-1);
				}
				ans+=res;
				for(int l=0;l<4;l++)
					upd(v[l],1);
				to: ;
			}
			upd(h[j],1);
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：int08 (赞：2)

## 前言

模拟赛考的这个，机房某同学不想清楚就开写，于是怒玩 7k7k 小游戏（指代码长度达到了 $7\times 10^3$ 字节）喜提“机房耐写王”称号。

这里给一下我的实现，长度 $1.09\times10^3$ 字节，并不是最短解。

实现方案与其他题解略不同。

# Solution

### 如何考虑旋转算重

题目中说了能够旋转成一样的算一种情况，这样就很容易算重。

所以我们可以**钦定数字最小的一面向前且数字是正立的**，这样仍然统计得到所有情况。

### 如何枚举

首先枚举前面。

然后考虑 $n$ 比较小，可以再枚举一个面，显然后面和前面两面就能确定所有 $8$ 个顶点的颜色，能带来最多的信息量，我们就**枚举后面**好了。

注意枚举后面时候还要**枚举它的方向**。

那么容易发现剩下 $4$ 个面所需的颜色已经完全确定，统计它们的总出现次数，对应计算答案即可。

出现次数显然使用哈希配合 `unordered_map` 食用。

### 如何定义哈希函数

由于 $c\le 10^3$ 直接用一个四位的 $10^3$ 进制数即可。

由于正方形也可以旋转，而且旋转后算不同情况，故具体方案是值得考虑的。

其他人的方案是：将旋转的四个方向都加入表中，然后简单处理一下算重的情况即可。

我的方案是：选取四个方向中最小值作为实际哈希值。

这样就可以把 `1,2,3,4` 和 `2,3,4,1` 这种旋转后相等的当成一种了。

值得注意的是由于某一块自己旋转算不同情况，故如果需要的正方形两对角颜色相等，这轮答案要乘 $2$，如果四角全相等要乘 $4$。

剩下的是一个排列问题（注意不是组合问题是因为上下左右是本质不同的面）。

## AC Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,i,j,c[404][10],b[8],k,l,x,ans;
int p1k[5]={1,1000,1000000,1000000000};
int get_hash(int a,int b,int c,int d)
{
	int ans=1e15,x[10]={a,b,c,d,a,b,c},an;
	for(int i=0;i<=3;i++)
	{
		an=0;
		for(int j=0;j<=3;j++) an+=x[i+j]*p1k[j];
		ans=min(ans,an);
	}
	return ans;
}
unordered_map<int,int> m,ch;
void add(int a,int b,int c,int d)
{
	if(a==c&&b==d) x*=(a==b?4:2);
	int hs=get_hash(a,b,c,d);
	x*=m[hs]-ch[hs];
	ch[hs]++;
}
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=3;j++) cin>>c[i][j];
		if(n-i<5) m[get_hash(c[i][0],c[i][1],c[i][2],c[i][3])]++;
		c[i][4]=c[i][0];
	}
	for(i=n-5;i>=1;i--)
	{
		for(j=i+1;j<=n;j++)
		{
			int hs=get_hash(c[j][0],c[j][1],c[j][2],c[j][3]);
			m[hs]--;
			for(k=0;k<=7;k++) b[k]=c[j][k%4];
			for(k=0;k<=3;k++)
			{
				x=1;
				for(l=0;l<=3;l++) add(c[i][l+1],c[i][l],b[k+4-l],b[k+4-l-1]);
				ans+=x;
				ch.clear();
			}
			m[hs]++;
		}
		m[get_hash(c[i][0],c[i][1],c[i][2],c[i][3])]++;
	}
	cout<<ans;
	return 0;
}
```
# The End.

---

## 作者：gghack_Nythix (赞：1)

## 前言：

[题目传送门](https://www.luogu.com.cn/problem/AT_arc062_c)

模拟赛考了这一题，但是比赛最后5分钟才发现面也可以旋转，并且判随机数据点还放在了暴力后面.......

## 分析：

其实拿到题目，你可以考虑枚举 $6$ 个面然后进行大模拟一般的判断。但是数据不支持我们这么做，所以考虑别的方法（当然如果有兴趣也可以自行讨论一下，反正我写了一页）。

然后深入观察，发现：

- 只要确定了两个相对的面，整个正方体其实也就确定了。

那么我们可以考虑枚举正方体的对立两个面，尝试旋转其中的一个面，并对其统计答案，具体的，设 $t_S$ 表示四个角颜色状态为 $S$ 的正方形个数，则：

$$
ans=\sum\limits_{\text{枚举的面}}\prod\limits_{\text{除了前面和后面的面}} t_{S}
$$

然后统计的时候记得去一下重，可以使用哈希来判定面的相似性。

然后这一题就做完了：

放一下恶臭的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node {
	int leftup,rightup,rightdown,leftdown,id;
}q[2005];
int n,ans = 0;
int suf_hash[2005];
int make_hash(node q) {
	int re = 0;
	re += (q.leftup);
	re += (q.rightup << 10);
	re += (q.rightdown << 20);
	re += (q.leftdown << 30);
	return re;
}//其实就是制造hash值，因为颜色1000种，这样子可以保证数位不重复，即每一位对应一个独特的颜色hash
unordered_map<int,int>tot;
void addtag(int hashv,int d){tot[hashv] += d;return void();} 
void rotate(node &q) {
	node q2 = q;
	q.leftup = q2.leftdown;
	q.rightup = q2.leftup;
	q.rightdown = q2.rightup;
	q.leftdown = q2.rightdown;
}//旋转
void adt(node q,int d){for(int i = 0;i < 4;++i) addtag(make_hash(node{q.leftup,q.rightup,q.rightdown,q.leftdown}),d),rotate(q);}//给面的每一种旋转情况打上一个标记
int surface_sidecalc[205];
node suf_sta[205];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;++i){
		cin >> q[i].leftup >> q[i].rightup >> q[i].rightdown >> q[i].leftdown,q[i].id = i;
		suf_hash[i] = make_hash(q[i]);
		adt(q[i],1);
	}
	for(int pre_suf = 1;pre_suf <= n - 5;++pre_suf) {
		adt(q[pre_suf],-1);//去重，后面不加回来，这个面算过了。
		for(int bk_suf = pre_suf + 1;bk_suf <= n;++bk_suf) {
			adt(q[bk_suf],-1);
			for(int p = 0;p < 4;++p){
				int Ts = 1;
				node suf_left = {q[bk_suf].rightup,q[pre_suf].leftup,q[pre_suf].leftdown,q[bk_suf].rightdown};
				node suf_right = {q[pre_suf].rightup,q[bk_suf].leftup,q[bk_suf].leftdown,q[pre_suf].rightdown};
				node suf_up = {q[pre_suf].leftup,q[bk_suf].rightup,q[bk_suf].leftup,q[pre_suf].rightup};
				node suf_down = {q[pre_suf].leftdown,q[pre_suf].rightdown,q[bk_suf].leftdown,q[bk_suf].rightdown};
				surface_sidecalc[0] = make_hash(suf_left);
				suf_sta[0] = suf_left;
				surface_sidecalc[1] = make_hash(suf_right);
				suf_sta[1] = suf_right;
				surface_sidecalc[2] = make_hash(suf_up);
				suf_sta[2] = suf_up;
				surface_sidecalc[3] = make_hash(suf_down);
				suf_sta[3] = suf_down;//上面这一坨都是在统计旋转和其他的面的颜色情况
				if(tot[surface_sidecalc[0]]==0 || tot[surface_sidecalc[1]]==0 || tot[surface_sidecalc[2]]==0 || tot[surface_sidecalc[3]]==0) {rotate(q[bk_suf]);continue;}//玄学优化
				for(int i = 0;i < 4;++i) Ts *= tot[surface_sidecalc[i]],adt(suf_sta[i],-1);//防止算重
				for(int i = 0;i < 4;++i) adt(suf_sta[i],1);//加回来下次还要算
				rotate(q[bk_suf]);
				ans += Ts;
			}
			adt(q[bk_suf],1);
		}
	}
	return cout << ans << '\n',0;//恶臭代码写了我2h
}
```

---

## 作者：Locix_Elaina_Celome (赞：0)

建议降绿。

先考虑忽略合法性的总方案数，或者说所有颜色都相等的方案数。

$n$ 个选 6 个来顺序排，然后每块有 4 种排法。一个正方体会被重复算 24 次。

所以 $ans=\frac{A_{n}^6\times 4^6}{24}$。

然后考虑暴力，直接 $O(A_{n}^6\times 4^6)$ 暴力枚举然后 check。

然后发现顶上底下的“盖子”不用枚举，因为颜色已经确定了，数数就行了。

再进一步发现只需要枚举相对的两面就可以确定全部了。

然后考虑怎么数数。

可以把每块瓷砖的颜色按照顺序哈希存下来，转圈四个排法都存。设 $h_{i,0/1/2/3}$ 表示 $i$ 这个瓷砖转 $0/1/2/3$ 下的哈希值。

然后设 $cnt_i$ 表示 $i$ 这个哈希值出现的次数。

设 $nxt_i$ 表示把 $i$ 这个哈希值对应的状态转一下对应的哈希值。

然后就可以枚举了，枚举出一块就把对应四个哈希值的 $cnt$ 减少。计数的时候每数一个就把这个哈希值以及其转圈圈之后的哈希值全部减一。最后全部加回来。

说着有点复杂，看代码应该能看懂。


```cpp

int n;
int col[N][10];
int h[N];
int tot;
struct mp1{
	int a[100000000];
	int& operator [] (ULL x){return a[x%100000007];}
}cnt;
struct mp2{
	ULL a[100000000];
	ULL& operator [] (ULL x){return a[x%100000007];}
}nxt;
ULL hs[N][10];
ULL f(int a,int b,int c,int d){
	return a*P*P*P+b*P*P+c*P+d; 
}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(col[i][0]),read(col[i][1]),read(col[i][2]),read(col[i][3]);
		h[++tot]=col[i][0];
		h[++tot]=col[i][1];
		h[++tot]=col[i][2];
		h[++tot]=col[i][3];
	}
	sort(h+1,h+tot+1);
	tot=unique(h+1,h+tot+1)-h-1;
	for(int i=1;i<=n;i++){
		col[i][0]=lower_bound(h+1,h+tot+1,col[i][0])-h;
		col[i][1]=lower_bound(h+1,h+tot+1,col[i][1])-h;
		col[i][2]=lower_bound(h+1,h+tot+1,col[i][2])-h;
		col[i][3]=lower_bound(h+1,h+tot+1,col[i][3])-h;
		cnt[hs[i][0]=f(col[i][0],col[i][1],col[i][2],col[i][3])]++;
		cnt[hs[i][1]=f(col[i][1],col[i][2],col[i][3],col[i][0])]++;
		cnt[hs[i][2]=f(col[i][2],col[i][3],col[i][0],col[i][1])]++;
		cnt[hs[i][3]=f(col[i][3],col[i][0],col[i][1],col[i][2])]++;
		nxt[hs[i][0]]=hs[i][1];
		nxt[hs[i][1]]=hs[i][2];
		nxt[hs[i][2]]=hs[i][3];
		nxt[hs[i][3]]=hs[i][0];
	}
	int ans=0;
	for(int a=1;a<=n;a++){
		for(int fa=0;fa<4;fa++){
			cnt[hs[a][0]]--;
			cnt[hs[a][1]]--;
			cnt[hs[a][2]]--;
			cnt[hs[a][3]]--;
			for(int b=1;b<=n;b++){
				if(b==a)continue;
				for(int fb=0;fb<4;fb++){
					cnt[hs[b][0]]--;
					cnt[hs[b][1]]--;
					cnt[hs[b][2]]--;
					cnt[hs[b][3]]--;
					int u=1;
					int x;
					
					u=u*cnt[f(col[b][(fb+3)&3],col[b][(fb+2)&3],col[a][(fa+1)&3],col[a][(fa+0)&3])]%P;
					x=f(col[b][(fb+3)&3],col[b][(fb+2)&3],col[a][(fa+1)&3],col[a][(fa+0)&3]);
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					
					u=u*cnt[f(col[a][(fa+3)&3],col[a][(fa+2)&3],col[b][(fb+1)&3],col[b][(fb+0)&3])]%P;
					x=f(col[a][(fa+3)&3],col[a][(fa+2)&3],col[b][(fb+1)&3],col[b][(fb+0)&3]);
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					
					u=u*cnt[f(col[b][(fb+3)&3],col[a][(fa+0)&3],col[a][(fa+3)&3],col[b][(fb+0)&3])]%P;
					x=f(col[b][(fb+3)&3],col[a][(fa+0)&3],col[a][(fa+3)&3],col[b][(fb+0)&3]);
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					
					u=u*cnt[f(col[a][(fa+1)&3],col[b][(fb+2)&3],col[b][(fb+1)&3],col[a][(fa+2)&3])]%P;
					x=f(col[a][(fa+1)&3],col[b][(fb+2)&3],col[b][(fb+1)&3],col[a][(fa+2)&3]);
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					cnt[x]--;x=nxt[x];
					
					
					ans=(ans+u)%P;
					
					
					x=f(col[b][(fb+3)&3],col[b][(fb+2)&3],col[a][(fa+1)&3],col[a][(fa+0)&3]);
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					
					x=f(col[a][(fa+3)&3],col[a][(fa+2)&3],col[b][(fb+1)&3],col[b][(fb+0)&3]);
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					
					x=f(col[b][(fb+3)&3],col[a][(fa+0)&3],col[a][(fa+3)&3],col[b][(fb+0)&3]);
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					
					x=f(col[a][(fa+1)&3],col[b][(fb+2)&3],col[b][(fb+1)&3],col[a][(fa+2)&3]);
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					cnt[x]++;x=nxt[x];
					
					
					cnt[hs[b][0]]++;
					cnt[hs[b][1]]++;
					cnt[hs[b][2]]++;
					cnt[hs[b][3]]++;
				}
			}
			cnt[hs[a][0]]++;
			cnt[hs[a][1]]++;
			cnt[hs[a][2]]++;
			cnt[hs[a][3]]++;
		}
	}
	write(ans*qp((int)24,P-2)%P);
	return 0;
}

```

---

