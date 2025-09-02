# Divide The Students

## 题目描述

最近有许多学生报名了 Berland 州大学。所有的学生被分到了不同的组，但后来人们发现有些组实在是太大了，以至于不能在同一个教室上课，因此这些组要被分成两个小组。你的任务是帮助学校把计算机科学学院一年级的学生分小组。

计算机科学学院一共有 $t$ 组学生。每个学生有三门功课：数学、编程和体育。每门课的教室不一样——数学课在礼堂上，编程课在机房上，体育课在体育馆上。

每一组都要被分成两个小组，使得每个小组的每个教室都能够容纳这个小组来上这一门课的所有学生。对于第 $i$ 个组的第一个小组，数学课的上课地点是一个可以容纳 $a_{i,1}$ 个学生的礼堂，编程课的上课地点是一个可以容纳 $b_{i,1}$ 个学生的机房，体育课的上课地点是一个可以容纳 $c_{i,1}$ 个学生的体育馆。类似地，第二个小组的礼堂、机房和体育馆分别可以容纳 $a_{i,2},b_{i,2},c_{i,2}$ 个学生。

和通常一样，有些学生会翘课。每个学生都认为，这三门功课中的 $0\sim 3$ 门是没用的，他会翘掉这些他认为没用的课，只上其他的课。这个数据会按下面的格式给出。第 $i$ 个组有：

1. $d_{i,1}$ 名学生上所有的课
2. $d_{i,2}$ 名学生上数学和编程课
3. $d_{i,3}$ 名学生上数学和体育课
4. $d_{i,4}$ 名学生只上数学课
5. $d_{i,5}$ 名学生上编程和体育课
6. $d_{i,6}$ 名学生只上编程课
7. $d_{i,7}$ 名学生只上体育课

事实上还有一些什么课都不上的学生，他们不会占用任何教室空间，所以在这个问题中我们不需要知道他们有多少人，处理他们是教务处的事（大雾）。

你的任务是把每一个组分成两个小组，使得每个小组的礼堂、机房和体育馆都有足够的空间容纳这个小组要上这门课的学生（如果可能的话）。第 $i$ 个组的每一个学生都必须恰属于某一个小组（第一小组或第二小组），禁止在组之间调剂学生（不服从调剂）。

## 样例 #1

### 输入

```
3
9 4 13
1 10 3
1 2 3 4 5 6 7
9 4 13
1 10 3
2 1 3 4 5 6 7
1 2 3
4 5 6
0 0 0 0 0 0 0
```

### 输出

```
1 1 3 4 2 0 7
-1
0 0 0 0 0 0 0
```

# 题解

## 作者：Sweetlemon (赞：7)

### CF1271F Divide The Students

我一开始根据初中数学套路列了不等式，然后要判断七元不等式组是否有整数解？我想还是算了。

那么怎么办呢？是不是可以动态规划？好像又没有什么思路……

打开 [tutorial](https://codeforces.com/blog/entry/72247) 一看，真是太神奇了……

下面简述思路。

首先，你可能经历了和我上面一样的心路历程。发现没办法做了？

接着，如果这是 OI 赛制的含部分分题目，那么你应该会在“数据范围”一栏看到一些“特殊性质”。现在没有“特殊性质”，就让我们来自己脑补！

1. 如果所有学生都翘课，那么直接输出 $7$ 个 $0$ 就好了～生活好轻松……
2. 如果所有的学生都只上一门课，那么这个问题很容易解决，只要 $a_{i,1}+a_{i,2}\ge d_{i,4},b_{i,1}+b_{i,2}\ge d_{i,6},c_{i,1}+c_{i,2}\ge d_{i,7}$ 即有解，分配时也可以随意地把学生分组，每个小组数学、编程和体育的承载力分别为 $a_{i,j},b_{i,j},c_{i,j}$。
3. 如果所有的学生都只上两门课。那么似乎不知道怎么解决？这档部分分先跳过。
4. 如果所有学生都上完三门课，那么只要 $\min(a_{i,1},b_{i,1},c_{i,1})+\min(a_{i,2},b_{i,2},c_{i,2})\ge d_{i,1}$ 即有解，分配时同样可以把学生分组，每个小组的承载力为 $\min(a_{i,j},b_{i,j},c_{i,j})$。

这是一些比较容易想到的部分分。由于第 2 种和第 4 种情况我们都很容易解决，因此还可以造出这样的部分分：

5. 如果所有的学生要么只上一门课，要么上完三门课，那么只要先分配上完三门课的学生，再分配只上一门课的学生即可。

上面这些部分分都很好做，$O(1)$ 就做完了。

可是一旦加上了“上两门课的学生”，问题就困难了不少！怎么办呢？

OI 赛制下如果想不到解决办法怎么办？暴力啊。

这里也有一种暴力：先枚举只上两门课的学生的分组情况，这样就转变为了第 5 种部分分的情况，可以再花 $O(1)$ 时间解决。由于只上两门课的学生有三种，要分别枚举这三种学生的分组情况，因此需要三重循环，总复杂度 $O(n^3)$ 级别。

什么？你告诉我已经做完了？我怎么不相信！难道 $n^3$ 能过 $3000$？

事实上，这题似乎真能过。由于学生总人数不超过 $3000$，因此选两门课的三类学生人数（分别记作 $x,y,z$）满足 $x+y+z\le 3000$。总计算量至多是 $xyz$，根据均值不等式，$xyz\le (\frac{x+y+z}{3})^3=10^9$。由于这题有 $8\mathrm{s}$ 时限，因此平均到每一秒的计算量大约是 $1.25\times 10^8$，对一个不是很复杂的算法来说勉强可过。何况由于可以随手写一些剪枝，这个计算量也很难达到。

综上，复杂度 $O(n^3)= O(\text{能过})$！事实上，（据出题人所说）不加剪枝的程序在最慢的点只跑了 $1.8\mathrm{s}$，我的加了简单剪枝的程序（见下）在最慢的点只跑了 $46\mathrm{ms}$。

这题的主要启示就是，要善于把问题特殊化（想部分分），并能从部分分中得到原问题的解。事实上，这种思维方法在 NOIP 中也有多次出现。另外，还要适当估算时间复杂度，敢于写 $O(\text{玄学})$。

```cpp
#include <cstdio>
#include <cctype>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
#define LOWBIT(x) ((x)&(-(x)))
using namespace std;

typedef long double ld;
typedef long long ll;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void); //快读，实现略去
void ayano(io_t x,char spliter='\n'); //快写，实现略去

int a1,b1,c1,a2,b2,c2;
int dabc,da,db,dc,dab,dac,dbc;

int check(void);
int min(int a,int b);
int min(int a,int b,int c);

int main(void){
    int testdatas=seto();
    while (testdatas--){
        a1=seto(),b1=seto(),c1=seto();
        a2=seto(),b2=seto(),c2=seto();
        dabc=seto(),dab=seto(),dac=seto(),
        da=seto(),dbc=seto(),db=seto(),
        dc=seto();
        for (int tab=0,uab=min(dab,min(a1,b1));tab<=uab;tab++){
            if (dab-tab>min(a2,b2))
                continue;
            a1-=tab,b1-=tab,a2-=(dab-tab),b2-=(dab-tab);
            for (int tac=0,uac=min(dac,min(a1,c1));tac<=uac;tac++){
                if (dac-tac>min(a2,c2))
                    continue;
                a1-=tac,c1-=tac,a2-=(dac-tac),c2-=(dac-tac);
                for (int tbc=0,ubc=min(dbc,min(b1,c1));tbc<=ubc;tbc++){
                    if (dbc-tbc>min(b2,c2))
                        continue;
                    b1-=tbc,c1-=tbc,b2-=(dbc-tbc),c2-=(dbc-tbc);
                    if (check()){
                        int fabc=min(min(a1,b1,c1),dabc);
                        a1-=fabc,b1-=fabc,c1-=fabc;
                        int fa=min(a1,da);
                        int fb=min(b1,db);
                        int fc=min(c1,dc);
                        ayano(fabc,' '),ayano(tab,' '),ayano(tac,' '),
                        ayano(fa,' '),ayano(tbc,' '),ayano(fb,' '),
                        ayano(fc);
                        goto nowok; //偷懒用 goto，勿喷
                    }
                    b1+=tbc,c1+=tbc,b2+=(dbc-tbc),c2+=(dbc-tbc);
                }
                a1+=tac,c1+=tac,a2+=(dac-tac),c2+=(dac-tac);
            }
            a1+=tab,b1+=tab,a2+=(dab-tab),b2+=(dab-tab);
        }
        ayano(-1);
        nowok: ;
    }
    

    return 0;
}

inline int min(int a,int b){
    return (a<b)?(a):(b);
}
inline int min(int a,int b,int c){
    return min(min(a,b),c);
}

int check(void){
    int tmn1=min(a1,b1,c1);
    int tmn2=min(a2,b2,c2);
    if (tmn1+tmn2<dabc)
        return 0;
    if (a1+a2-dabc>=da && b1+b2-dabc>=db && c1+c2-dabc>=dc)
        return 1;
    return 0;
}

//以下略去读入输出优化的实现
```

---

## 作者：一念之间、、 (赞：4)

## 题意简述

说：给定 $7$ 类学生，保证学生总数在 $3000$，$3$ 种课，每一类学生 $1,2,3$ 种课上或者不上各是一种情况 $001,010,011,100,101,110,111$，不存在三种课都不上的学生，你需要把学生分成两组，对于第一组而言，满足三门课分别至多 ${a,b,c}$ 个学生来上，第二组而言，分别至多 $A,B,C$ 种学生来上，问：构分组方案，或者报告不合法。

## 题解

这里介绍一种严格 $O(n^2)$ 的做法，官方题解是 $O(n^3)$ 是我没想到的。

尝试贪心的解决这个问题，你注意到，对于 $111$ 我们先放到一边，最后讨论。

我们认为 $\operatorname{popcount} = 1$ 的学生分组后会使得一边的某课程容量 $-1$。

我们认为 $\operatorname{popcount} = 2$ 的学生分组后会使得一边所有课程容量 $-1$ 然后某课程容量 $+1$。

枚举 $A$ 作为第一组所有可能容量 $-1$ 的次数（包含分到第一组的 $111$ 数量和 $\operatorname{popcount}=2$ 的数量，代码实现中的 $i$），注意到，显然只需要枚举到总人数即可，同理枚举 $B$。

以下说明第一组的操作，第二组完全一致。

首先用 $\operatorname{popcount}=2$ 的元素进行 $+1$ 操作使得第一组三个容量至少为 $A$，贪心的，多余容量可以分给 $\operatorname{popcount}=1$ 的元素。

你会发现目前并没有完全消耗掉 $A$，设还剩 $t$，对于消耗剩下元素，你的处理方式是，优先将对应 $\operatorname{popcount}=1$ 和 $\operatorname{popcount} =2$ 分组，若不存在配对关系，则 $\operatorname{popcount}=2$ 独立分组，或者对应三个 $\operatorname{popcount}=1$ 的分为一组。

检查第一组和第二组的 $t$ 的加和是否足够，构方案是简单的。

正确性是显然的，因为你目前对于所有情况，总会在枚举 $A,B$ 的过程中被计算到。

复杂度 $O(n^2)$。

稍作思考，如果你只枚举第一组的 $A$ 然后尝试贪心，尝试讨论第二组的 $B$ 可以怎么取，进行处理，我的感觉是可做的，这也是我最开始的想法，但是发现进一步讨论过于繁琐，所以便改成了 $A,B$ 都枚举的处理方式，但我认为，在麻烦的讨论后，这道题可以做到 $O(n)$，各位读者也可以简单尝试一下。

## 代码

```cpp
#include<bits/stdc++.h>
namespace ifzw{
//~ #define int LL
#define ll long long
#define dd double
#define ull unsigned ll 
#define LL __int128
#define siz(A) ((int)A.size())
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&(s==t)))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(op,0);
}
char ST;
array<int,3>a,A;
int d[123],D[123];
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	#ifdef AAA
	system("ulimit -s 524288");
	cerr<<" stack is on \n";
	#endif 
	//~ freopen("a.in","r",stdin);
	//~ freopen("a.out","w",stdout);
	int T=read();
	while(T--)
	{
		//反了，我的是 PE pro Mt
		a={read(),read(),read()};
		A={read(),read(),read()};
		reverse(a.begin(),a.end());
		reverse(A.begin(),A.end());
		//~ int t[3]={0,0,0};
		//~ for(int i=0;i<7;i++)
		//~ {
			//~ int re=read();
			//~ for(int j=0;j<3;j++)
			//~ if(!(i>>j&1))t[j]+=re;
		//~ }
			//~ for(int j=0;j<3;j++)cout<<t[j]<<" ";
			//~ puts("");
		int cr=0,lim=0;
		for(int i=0;i<7;i++)d[i]=read(),lim+=d[i];
		//注意，这边的 +1 是不能给对面的。
		//贪心的，尽量消耗
		vector<int>an;
		for(int i=0;i<=lim;i++)
		{
			for(int j=0;j<=lim;j++)
			{
				for(int k=0;k<7;k++)D[k]=d[k];
				int lrem=0,rrem=0;
				vector<int>fn(7);
				for(int w=0;w<=2;w++)
				{
					fn[7-(1<<w)]+=min(max(0,a[w]-i),D[7-(1<<w)]);
					D[7-(1<<w)]-=max(0,a[w]-i);
				}
				for(int w=0;w<=2;w++)D[7-(1<<w)]-=max(0,A[w]-j);
				for(int k=0;k<7;k++)D[k]=max(D[k],0);
				int lu=0,ru=0;
				int ct=1;
				for(int w=0;w<=2;w++)
				{
					if(D[(1<<w)]<max(0,i-a[w]))ct=0;
					fn[1<<w]+=max(0,i-a[w]);
					D[(1<<w)]-=max(0,i-a[w]),lu+=max(0,i-a[w]);
				}
				for(int w=0;w<=2;w++)
				{
					if(D[(1<<w)]<max(0,j-A[w]))
					{
						
						//~ if(i==7&&j==4)cerr<<w<<" "<<ru<<" "<<ct<<" "<<A[w]<<" "<<D[(1<<w)]<<"@\n";
						ct=0;
					}
					D[(1<<w)]-=max(0,j-A[w]),ru+=max(0,j-A[w]);
				}
				//if(i==7&&j==4)cerr<<ru<<" "<<ct<<"@\n";
				if(lu>i||ru>j||!ct)
				{
					continue;
				}
				lrem=i-lu,rrem=j-ru;
				int tt=D[0];
				vector<int>cs(8);
				for(int w=0;w<=2;w++)
				{
					tt+=D[(1<<w)];
					cs[(1<<w)]=min(D[(1<<w)],D[7-(1<<w)]);
					D[7-(1<<w)]-=D[(1<<w)];
				}
				int rt=0;
				for(int w=0;w<=2;w++)
				{
					rt=max(rt,D[7-(1<<w)]);
					//~ cerr<<w<<" "<<D[7-(1<<w)]<<"!!!!\n";
				}
				//cerr<<lrem<<" SS "<<rrem<<" "<<tt<<" "<<lu<<" "<<ru<<" "<<i<<" "<<j<<" "<<rt<<"!\n";
				
				if(lrem+rrem>=rt+tt)
				{
					//~ cerr<<"@#@#######\n";
			//~ for(auto it:fn)cout<<it<<' ';puts("");
					cr=1;
					while(lrem&&D[0])--lrem,fn[0]++,--D[0];
					for(int w=0;w<=2;w++)
					{
						while(lrem>0&&D[1<<w])
						{
							--lrem,fn[1<<w]++,--D[1<<w];
							if(cs[1<<w])
							{
								//~ cerr<<w<<" "<<cs[(1<<w)]<<"@\n";
			//~ for(auto it:fn)cout<<it<<' ';puts("");
								fn[7-(1<<w)]++,--cs[1<<w];
							}
						}
					}
					while(lrem>0&&(D[3]>0||D[5]>0||D[6]>0))
					{
						--lrem;
						if(D[3]>0)fn[3]++,D[3]--;
						if(D[5]>0)fn[5]++,D[5]--;
						if(D[6]>0)fn[6]++,D[6]--;
						//~ D[3]--,D[5]--,D[6]--;
					}
					an=fn;
					break;
				}
			}
			if(cr)break;
		}
		if(cr)
		{
			for(auto it:an)cout<<it<<' ';
			puts("");
		}
		else puts("-1");
		
	}
	pc('1',1);
	return 0;
}

}signed main(){return ifzw::main();}

```



---

## 作者：serene_analysis (赞：3)

第三种严格 $\mathcal{O}(n^2)$ 的做法。

先判掉明显的无解情况，也就是存在一种容量不够。我们先忽略掉只上一种课的学生，这是因为没有容量被浪费，那么如果上至少两种课的学生能够成功分配，只上一种课的学生一定能放得完。枚举上课情况为 $110$ 和 $011$ 的学生分别分多少个给第一组，考虑第一组剩的容量，假设分别为 $a,b,c$，设 $mi=\min(a,c)$。这个时候还剩下 $101$ 和 $111$ 两种学生没有分配，设分配 $x$ 个 $101$ 学生，$y$ 个 $111$ 学生，我们进行简单的分类讨论：

+ $mi \leq b$，分配 $101$ 和 $111$ 两种学生都会使得 $mi$ 变小 $1$，那么分配的总和不能超过 $mi$，也即 $x+y \leq mi$。
+ $mi \gt b$，则 $x \leq mi-b$ 时 $y \leq b$，$x \gt mi-b$ 时 $x+y \leq mi$。

根据贪心策略，当 $x$ 固定时 $y$ 一定会取最大值，不妨分别改写三种可能结果为 $y=mi-x,x \in [0,mi]$，$y=b,x \in [0,mi-b]$，$y=mi-x,x \in [mi-b+1,mi]$，可见三者都是斜率为 $0$ 或 $-1$ 的一次函数。也就是说，现在的问题变成了对于两个大小不超过 $2$ 的线段的集合，从两个集合中各取一条线段，每条线段上各取一个点，要求两个点的横坐标和为某个定值，问纵坐标能否大于某个定值。那么如果存在斜率为 $0$ 的线段，其一定取到右端点，否则两个点的横坐标之和加纵坐标之和为定值，二者都可以简单判断。时间复杂度 $\mathcal{O}(n^2)$。细节有点多，具体实现时可以牺牲一点常数换取更简单的实现。

```cpp
#include<algorithm>
#include<cassert>
#include<cstdio>
#include<vector>
const int maxn=3e3+5;
int t;
int ga[2],gb[2],gc[2];
int d[8];
struct seg{int xl,xr,y,coe;};
std::vector<seg> go(int da,int db,int dc,int id){
	int a=ga[id]-da,b=gb[id]-db,c=gc[id]-dc,mi=std::min(a,c);
	if(a<0||b<0||c<0)return {};
	if(mi<=b)return {(seg){0,mi,mi,-1}};
	else return {(seg){0,mi-b,b,0},(seg){mi-b+1,mi,mi,-1}};
}
void report(int i,int j,int k,int l,int tp){
	int dec[8]={-1,i,j,k,std::min(d[4],ga[tp]-i-j-k),
		l,std::min(d[6],gb[tp]-i-j-l),std::min(d[7],gc[tp]-i-k-l)};
	for(int i=1;i<=7;i++)printf("%d ",tp?d[i]-dec[i]:dec[i]);
	printf("\n");
	return;
}
signed main(){
	scanf("%d",&t);
	for(int wc=1;wc<=t;wc++){
		scanf("%d%d%d%d%d%d",ga,gb,gc,ga+1,gb+1,gc+1);
		for(int i=1;i<=7;i++)scanf("%d",d+i);
		int ta=ga[0]+ga[1]-d[1]-d[2]-d[3]-d[4],
			tb=gb[0]+gb[1]-d[1]-d[2]-d[5]-d[6],
			tc=gc[0]+gc[1]-d[1]-d[3]-d[5]-d[7];
		if(std::min(std::min(ta,tb),tc)<0){
			printf("-1\n");
			continue;
		}
		bool found=false;
		for(int i=0;i<=d[2]&&!found;i++)for(int j=0;j<=d[5]&&!found;j++)for(int k=0;k<=1&&!found;k++){
			std::vector<seg>lef=go(i,i+j,j,k),rig=go(d[2]-i,d[2]+d[5]-i-j,d[5]-j,k^1);
			for(seg l:lef){
				if(found)break;
				for(seg r:rig){
					if(found)break;
					if(l.xl>l.xr||r.xl>r.xr)continue;
					if(l.xr+r.xr<d[3]||l.xl+r.xl>d[3])continue;
					if(r.coe==0&&l.coe!=0)continue;
					if(l.coe==0){
						int nl=std::max(r.xl,d[3]-l.xr);
						if(l.y+r.y+r.coe*nl>=d[1])
							found=true,report(std::min(d[1],l.y),i,std::min(d[3],l.xr),j,k);
					}
					else{
						if(l.y+r.y>=d[1]+d[3]){
							int rused=l.xl,left=d[3]-l.xl-r.xl;
							rused+=std::min(left,l.xr-l.xl);
							found=true,report(std::min(d[1],l.y-rused),i,rused,j,k);
						}
					}
				}
			}
		}
		if(!found)printf("-1\n");
	}
	return 0;
}
//namespace burningContract
```

感谢你的阅读。

---

## 作者：lgvc (赞：2)

提供一种 $O(N)$ 做法。

题面等价于：

构造出 $ans_1,ans_2,ans_3,ans_4,ans_5,ans_6,ans_7$，他们不超过对应的 $d$ 且要求 $ans_1+ans_2+ans_3+ans_4$，$ans_1+ans_2+ans_5+ans_6$，
$ans_1+ans_3+ans_5+ans_7$ 在三个给定的区间内。$T$ 组数据。

枚举 $ans_1+ans_2$。计算出 $ans_3+ans_4,ans_5+ans_6$ 的范围。在这些范围的基础上，进一步计算 $ans_1,ans_3,ans_5,ans_7$ 的范围。注意到这因为是一个连续的范围，所以只要 $ans_1+ans_3+ans_5+ans_7$ 和给定的要求区间有交，那么就可以构造出解。

恶心的 [代码](https://www.luogu.com.cn/paste/pzfbx5cs)。

容易发现，循环枚举的 $i$ 的有解条件可以拆为 $O(1)$ 个段，每一个段都是一次不等式，所以应该可以 $O(1)$ 求解。

---

## 作者：mazihang2022 (赞：1)

提供一种 $O(n^2)$ 做法。

不难发现一般情况下，将某间教室占满一定不会更劣。证明可以考虑调整，尽可能占满其中的某一间，如果调整不动了肯定意味着有另一间占满了。当然还有一种情况是怎么调整都占不满任意一间教室，这时不难发现任意分配方案都是合法的。

将只上一门课的留到最后考虑。枚举满的那一间教室，假设是第一组第一间，那么只有 $111,110,101$（$0/1$ 表示上不上某门课）这三类人会对此有影响。由于钦定这间教室占满，我们只需要枚举其中两类人分到第一组的人数，剩下的就只有 $011,100,010,001$ 这几类人需要考虑了，直接贪心选择即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fir first
#define sec second
#define pii pair<int,int>
using namespace std;

const int maxn=1000005;
const int inf=0x3f3f3f3f;

namespace Solve {
	int d[8];
	int td[8];
	int a[2],b[2],c[2];
	int ta[2],tb[2],tc[2];
	bool solve(int x,int y,int ff) {
		for(int i=1;i<=7;i++) {
			int t=i;
			if(((i>>x)&1)^((i>>y)&1)) {
				t=i^(1<<x)^(1<<y);
			}
			d[i]=td[t];
		}
		for(int i=0;i<=d[6];i++) {
			for(int j=0;j<=d[5];j++) {
				a[0]=ta[0],a[1]=ta[1];
				b[0]=tb[0],b[1]=tb[1];
				c[0]=tc[0],c[1]=tc[1];
				if(i+j>a[0]) {
					continue;
				}
				int k=min(a[0]-i-j,d[7]);
				a[0]-=i+j+k,b[0]-=i+k,c[0]-=j+k;
				if(b[0]<0||c[0]<0) {
					continue;
				}
				a[1]-=(d[7]-k)+(d[6]-i)+(d[5]-j);
				b[1]-=(d[7]-k)+(d[6]-i);
				c[1]-=(d[7]-k)+(d[5]-j);
				int t=min(min(b[0],c[0]),d[3]);
				b[0]-=t,c[0]-=t;
				b[1]-=(d[3]-t),c[1]-=(d[3]-t);
				int u=min(a[0],d[4]),v=min(b[0],d[2]),w=min(c[0],d[1]);
				a[0]-=u,b[0]-=v,c[0]-=w;
				a[1]-=(d[4]-u),b[1]-=(d[2]-v),c[1]-=(d[1]-w);
				if(a[1]<0||b[1]<0||c[1]<0) {
					continue;
				}
				vector<int> ans(8),res(8);
				ans={k,i,j,u,t,v,w};
				reverse(ans.begin(),ans.end());
				ans.insert(ans.begin(),0);
				if(ff==-1) {
					for(int i=1;i<=7;i++) {
						ans[i]*=-1;
						ans[i]+=d[i];
					}
				}
				for(int i=1;i<=7;i++) {
					int t=i;
					if(((i>>x)&1)^((i>>y)&1)) {
						t=i^(1<<x)^(1<<y);
					}
					res[i]=ans[t];
				}
				for(int i=7;i>=1;i--) {
					cout<<res[i]<<" ";
				}
				cout<<"\n";
				return true;
			}
		}
		return false;
	}
	bool solve(int v) {
		if(!solve(2,2,v)) {
			swap(ta[0],tb[0]);
			swap(ta[1],tb[1]);
			bool f=solve(2,1,v);
			swap(ta[0],tb[0]);
			swap(ta[1],tb[1]);
			if(!f) {
				swap(ta[0],tc[0]);
				swap(ta[1],tc[1]);
				bool f=solve(2,0,v);
				swap(ta[0],tc[0]);
				swap(ta[1],tc[1]);
				if(!f) {
					return false;
				}
			}
		}
		return true;
	}
	void main() {
		ios::sync_with_stdio(false);
		cin.tie(0),cout.tie(0);
		int T;
		cin>>T;
		while(T--) {
			cin>>ta[0]>>tb[0]>>tc[0]>>ta[1]>>tb[1]>>tc[1]>>td[7]>>td[6]>>td[5]>>td[4]>>td[3]>>td[2]>>td[1];
			if(!solve(1)) {
				swap(ta[0],ta[1]);
				swap(tb[0],tb[1]);
				swap(tc[0],tc[1]);
				if(!solve(-1)) {
					cout<<"-1\n";
				}
			}
		}
	}
}

signed main() {
	Solve::main();
}
```

---

