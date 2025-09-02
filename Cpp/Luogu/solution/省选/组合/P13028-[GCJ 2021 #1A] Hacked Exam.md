# [GCJ 2021 #1A] Hacked Exam

## 题目描述

一场考试包含 $\mathbf{Q}$ 道判断题，每道题的正确答案是 $\mathsf{T}$ 或 $\mathsf{F}$。每位考生为每道题选择 $\mathsf{T}$ 或 $\mathsf{F}$，其得分是答对的题数。

![](https://cdn.luogu.com.cn/upload/image_hosting/jwf5pdvs.png)

已有 $\mathbf{N}$ 名学生参加了这场考试。对于每名学生，你知道他们的答案和最终得分。假设所有与学生得分一致的正确答案序列出现的概率相同，你需要最大化自己的期望得分。请确定该期望得分，并给出能达到该得分的答题方案。

## 说明/提示

**样例解释**

在样例 #1 中，由于 $\mathsf{FFT}$ 的得分为 3，正确答案序列必须是 $\mathsf{FFT}$。

在样例 #2 中，由于 $\mathsf{FFT}$ 的得分为 2，正确答案序列可能是 $\mathsf{FFF}$、$\mathsf{FTT}$ 或 $\mathsf{TFT}$，每种概率为 $\frac{1}{3}$。最佳策略是回答 $\mathsf{FFT}$，期望得分为 $\frac{1}{3} \times 2 + \frac{1}{3} \times 2 + \frac{1}{3} \times 2 = 2$。

在样例 #3 中，其他答案（如 $\mathsf{FTFTFT}$）也能达到期望得分 4。

在样例 #4 中，一道题的答案是 $\mathsf{T}$，另一道是 $\mathsf{F}$，但无法确定顺序。回答 $\mathsf{TF}$ 或 $\mathsf{FT}$ 有 $\frac{1}{2}$ 概率得 2 分，$\frac{1}{2}$ 概率得 0 分，期望得分为 1。回答 $\mathsf{FF}$ 或 $\mathsf{TT}$ 保证得 1 分。由于所有答案序列的期望得分相同，可以输出任意一个。

样例 2 符合测试集 3 的限制。它不会用于测试你的提交。

在测试集 3 的样例中，你可以获得超过 65 的期望得分，高于其他学生的实际得分。注意，期望分数的分子和分母可能远大于 $2^{64}$（此样例的分子实际超过 $2^{97}$）。

**数据范围**

- $1 \leq \mathbf{T} \leq 2021$。
- 对于所有 $i$，$\mathbf{A}_{\mathbf{i}}$ 的长度为 $\mathbf{Q}$。
- 对于所有 $i$，$\mathbf{A}_{\mathbf{i}}$ 的每个字符是大写 $\mathsf{T}$ 或 $\mathsf{F}$。
- 对于所有 $i$，$0 \leq \mathbf{S}_{\mathbf{i}} \leq \mathbf{Q}$。
- 输入至少存在一个一致的正确答案序列。

**测试集 1（8 分，可见评测结果）**

- $1 \leq \mathbf{N} \leq 2$。
- $1 \leq \mathbf{Q} \leq 10$。

**测试集 2（6 分，隐藏评测结果）**

- $1 \leq \mathbf{N} \leq 2$。
- $1 \leq \mathbf{Q} \leq 40$。

**测试集 3（25 分，隐藏评测结果）**

- $1 \leq \mathbf{N} \leq 3$。
- $1 \leq \mathbf{Q} \leq 120$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1 3
FFT 3
1 3
FFT 2
2 6
FFTTTF 2
FTFTFT 4
2 2
FF 1
TT 1```

### 输出

```
Case #1: FFT 3/1
Case #2: FFT 2/1
Case #3: FTFFFT 4/1
Case #4: TF 1/1```

## 样例 #2

### 输入

```
1
3 120
FFTFFFTFFFTTTTTTTFTFFFFFFTTTFTFFFTFTFFTTFTFFTFFTTTFTFTFFTFTFTTFFFFTFTFFFFTTTFTTFTTTTFFFTTFFFFFTTFFTFFTFFTTTFFFFTTFFTFTTF 55
FFFTFFTTFFFFTFTFFTFFFTTTTTTFFFTTTFTTTTFFTFTTTFTTFFTTTFTFFFFTFFTTFFTTFTTFFTFTFFTFTTFTFTFFTTTFFTFTFTTFFTFTFTFTTFFTFFFTFTFT 62
FFFTFTTFFFFFTFTFTTTTTTFFTTFTFFFTFFTTTTTTFFFTTTFFFTTFTFFFFFFTFTTFFTFTTTFTTTTFTTFFFFTFFTTFTFFTTTTTTFTFFFFFTTFFTFTFTFFTTTTT 64```

### 输出

```
Case #1: FFFTFTTTFFFFTFTFFTFTTTTTTTFFFFTTTFTTTTFFTFTTTTTFFFTFTFTFFFFTFFTTFTFTFTTTTTFFTFFFFFFFFTTFTTTTTTFTTTTFFFFTFTFTTFTFFFFTTTFT 189154508532118369075350624633/2901503505434414233388602018```

# 题解

## 作者：gdf_yhm (赞：0)

[P13028](https://www.luogu.com.cn/problem/P13028)

### 思路

唯一能决定你在一道题的回答的只有其他 $n$ 个人在该题答案是否相同。

#### $n=1$

如果得分大于一半，就回答相同的答案；否则回答相反的答案。

#### $n=2$

设有 $num$ 个问题两人答案相同，另外 $n-num$ 题两人只有一人答对。所以对于两人答案相同的题目，有 $\frac{va+vb-(n-num)}{2}$ 道正确，如果多余一半就回答相同的，否则相反。对于剩下的 $n-num$ 题，得分高的人能更多，跟得分高的人回答。

#### $n=3$

设有 $num$ 个问题三人答案相同，$num1$ 个 $B,C$ 相同，$num2$ 个 $A,C$ 相同，$num3$ 个问题 $A,B$ 相同。

此时无法确定每类问题中有几个多数人的答案正确，设分别有 $w,x,y,z$ 个。则有 $va=w+num1-x+y+z$ 等三个等式，枚举 $w$ 后可以唯一确定另外三个。

每种问题，可以选择回答和多数人相同或相反。只需要对于每种可能的 $w,x,y,z$，对于 $2^4$ 种决策，分别算出得分乘对应方案数 $\binom{num}{w}\times \binom{num1}{x}\times \binom{num2}{y}\times \binom{num3}{z}$ 即可。方案数需要 ```__int128```。

复杂度 $O(Tm2^n)$。

### code

```cpp
int n,m;
char a[maxn],b[maxn],c[maxn];
int va,vb,vc;
ll C[maxn][maxn];
ll val[16];
ll gcd(ll a,ll b){return b==0?a:gcd(b, a%b);}
void work(){
    n=read();m=read();
    if(n==1){
        scanf("%s",a+1);va=read();
        if(va<=m/2){
            for(int i=1;i<=m;i++){
                if(a[i]=='F')a[i]='T';
                else a[i]='F';
            }
            va=m-va;
        }
        for(int i=1;i<=m;i++)cout<<a[i];cout<<" "<<va<<"/1"<<"\n";
    }
    if(n==2){
        scanf("%s",a+1);va=read();
        scanf("%s",b+1);vb=read();
        if(va<vb)swap(a,b),swap(va,vb);
        int num=0;for(int i=1;i<=m;i++)if(a[i]==b[i])++num;
        int cnt=(va+vb-m+num)/2,lst=va-cnt;
        if(cnt<=num/2){
            for(int i=1;i<=m;i++)if(a[i]==b[i]){
                if(a[i]=='F')a[i]='T';
                else a[i]='F';
            }
            cnt=num-cnt;
        }
        for(int i=1;i<=m;i++)cout<<a[i];cout<<" "<<cnt+lst<<"/1"<<"\n";
    }
    if(n==3){
        scanf("%s",a+1);va=read();
        scanf("%s",b+1);vb=read();
        scanf("%s",c+1);vc=read();
        int num=0,num1=0,num2=0,num3=0;
        for(int i=1;i<=m;i++){
            if(a[i]==b[i]&&a[i]==c[i])++num;
            else if(b[i]==c[i])++num1;
            else if(a[i]==c[i])++num2;
            else ++num3;
        }
        for(int s=0;s<16;s++)val[s]=0;ll tot=0;
        for(int w=0;w<=min({num,va,vb,vc});w++){
            va-=w+num1,vb-=w+num2,vc-=w+num3;
            int sum=va+vb+vc;
            int x=(sum-va)/2,y=(sum-vb)/2,z=(sum-vc)/2;
            va+=w+num1,vb+=w+num2,vc+=w+num3;
            if(x>=0&&x<=num1&&y>=0&&y<=num2&&z>=0&&z<=num3&&va==w+num1-x+y+z&&vb==w+num2-y+x+z&&vc==w+num3-z+x+y){
                ll cnt=C[num][w]*C[num1][x]*C[num2][y]*C[num3][z];tot+=cnt;
                for(int s=0;s<16;s++){
                    val[s]+=(ll)(((s&1)?num-w:w)+((s&2)?num1-x:x)+((s&4)?num2-y:y)+((s&8)?num3-z:z))*cnt;
                }
            }
        }
        pair<ll,int> mx={0,0};
        for(int s=0;s<16;s++)mx=max(mx,{val[s],s});
        for(int i=1;i<=m;i++){
            if(a[i]==b[i]&&a[i]==c[i]){
                if(mx.se&1){
                    if(a[i]=='F')a[i]='T';
                    else a[i]='F';
                }
            }
            else if(b[i]==c[i]){
                if(mx.se&2){
                    if(b[i]=='F')a[i]='T';
                    else a[i]='F';
                }
                else a[i]=b[i];
            }
            else if(a[i]==c[i]){
                if(mx.se&4){
                    if(a[i]=='F')a[i]='T';
                    else a[i]='F';
                }
            }
            else{
                if(mx.se&8){
                    if(a[i]=='F')a[i]='T';
                    else a[i]='F';
                }
            }
        }
        ll g=gcd(mx.fi,tot);
        mx.fi/=g,tot/=g;
        for(int i=1;i<=m;i++)cout<<a[i];cout<<" ";write(mx.fi);cout<<"/";write(tot);cout<<"\n";
    }
}
```

---

## 作者：gcx12012 (赞：0)

### 前言
小清新组合计数题，但是代码写的太史了有点难受。
### Solution
首先 $N\le 2$ 的情形是简单的，~~请读者自行思考。~~

这里直接考虑 $N=3$。由于 $T$ 比较大，显然我们需要一个单次 $O(Q^3)$ 的做法。

  一列大概有 $8$ 个状态，然后 `FFT` 和 `TTF` 是本质相同的，于是一列只有 $4$ 个不同状态，除去三个字符都相同的情况，只有 `FFT`，`FTF`，`TFF` 三种本质不同的状态，表示是否取出现次数较少的那个字符，设它们各有 $c_1,c_2,c_3$ 个，三个字符相同的有 $c_4$ 个，我们直接枚举 $i\le c_1,j\le c_2,k\le c_3$ 即可，然后在 $a_1-i=a_2-j=a_3-k$ 的前提下把合法方案数 $\binom{c_1}{i}\binom{c_2}{j}\binom{c_3}{k}\binom{c_4}{a_1-i}$ 加进 $sum$ 中。算每一位 `T` 和 `F` 的出现次数也是简单的，在总方案的基础上改动一下即可，然后取较大值加进 $ans$ 里，最后的答案就是 $\frac{ans}{sum}$。

时间复杂度应该是 $O(TQ^3)$ 的，实际上只跑了 71ms。

还是晒一下代码把，不喜勿喷。
```
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define ld long double
#define ull unsigned long long
#define lll __int128
#define N 500010
#define For(i,a,b) for(ll i=a;i<=b;++i)
#define Rof(i,a,b) for(ll i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define mk make_pair
#define pb push_back
#define pii pair<ll,ll>
#define pque priority_queue
#define fi first
#define se second

using namespace std;
lll C[130][130];
char s[3][210];
int T,n,m,a[3];

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void sc(lll x){
	if(x>=10) sc(x/10);
	int p=x%10;
	cout<<p;
}
lll gcd(lll x,lll y){
	if(!y) return x;
	return gcd(y,x%y);
}
void fenshu(lll x,lll y){
	lll d=gcd(x,y);
	x/=d,y/=d;
	cout<<' ';
	sc(x);
	cout<<"/";
	sc(y);
	cout<<endl;
}
lll C1(int u,int v){
	if(u<0 || v<0 || u<v) return 0;
	return C[u][v];
}
lll g[4][2];
char ans1[210];
void sol(int id){
	memset(g,0,sizeof(g));
	n=read(),m=read();
	For(i,0,n-1){
		cin>>(s[i]+1);
		a[i]=read();
	}
	printf("Case #%d: ",id);
	if(n==1){
		For(i,1,m){
			if(a[0]*2>=m){
				if(s[0][i]=='T') printf("T");
				else printf("F");
			}else{
				if(s[0][i]=='F') printf("T");
				else printf("F");
			}
		}
		fenshu(max(a[0],m-a[0]),1);
		return;
	}
	lll sum=0,ans=0;
	if(n==2){
		int c1=0,c2=0;
		For(i,1,m){
			if(s[0][i]==s[1][i]) c2++;
			else c1++;
		}
		For(i,0,c1){
			int f1=i,f2=c1-i;
			if(a[0]-f1==a[1]-f2 && a[0]-f1<=c2 && a[0]-f1>=0){
				sum+=C1(c1,i)*C1(c2,a[0]-f1);
				g[0][0]+=C1(c1-1,i-1)*C1(c2,a[0]-f1);
				g[0][1]+=C1(c1-1,i)*C1(c2,a[0]-f1);
				g[1][0]+=C1(c1,i)*C1(c2-1,a[0]-f1-1);
				g[1][1]+=C1(c1,i)*C1(c2-1,a[0]-f1);
			}
		}
		For(i,1,m){
			if(s[0][i]==s[1][i]) ans+=max(g[1][0],g[1][1]);
			else ans+=max(g[0][0],g[0][1]);
		}
		For(i,1,m){
			if(s[0][i]==s[1][i]){
				if(g[1][0]>=g[1][1]){
					if(s[0][i]=='T') printf("T");
					else printf("F");
				}else{
					if(s[0][i]=='F') printf("T");
					else printf("F");
				}
			}else{
				if(g[0][0]>=g[0][1]){
					if(s[0][i]=='T') printf("T");
					else printf("F");
				}else{
					if(s[0][i]=='F') printf("T");
					else printf("F");
				}
			}
		}
		fenshu(ans,sum);
		return;
	}
	int c1=0,c2=0,c3=0,c4=0;
	For(i,1,m){
		if(s[0][i]!=s[1][i] && s[0][i]!=s[2][i]) c1++;
		else if(s[1][i]!=s[0][i] && s[1][i]!=s[2][i]) c2++;
		else if(s[2][i]!=s[1][i] && s[0][i]!=s[2][i]) c3++;
		else c4++;
	}
	For(i,0,c1){
		For(j,0,c2){
			For(k,0,c3){
				int f1=i+c2-j+c3-k,f2=j+c1-i+c3-k,f3=k+c1-i+c2-j;
				if(a[0]-f1==a[1]-f2 && a[1]-f2==a[2]-f3 && a[0]-f1<=c4){
					sum+=C1(c1,i)*C1(c2,j)*C1(c3,k)*C1(c4,a[0]-f1);
					g[0][0]+=C1(c1-1,i-1)*C1(c2,j)*C1(c3,k)*C1(c4,a[0]-f1);
					g[0][1]+=C1(c1-1,i)*C1(c2,j)*C1(c3,k)*C1(c4,a[0]-f1);
					g[1][0]+=C1(c1,i)*C1(c2-1,j-1)*C1(c3,k)*C1(c4,a[0]-f1);
					g[1][1]+=C1(c1,i)*C1(c2-1,j)*C1(c3,k)*C1(c4,a[0]-f1);
					g[2][0]+=C1(c1,i)*C1(c2,j)*C1(c3-1,k-1)*C1(c4,a[0]-f1);
					g[2][1]+=C1(c1,i)*C1(c2,j)*C1(c3-1,k)*C1(c4,a[0]-f1);
					g[3][0]+=C1(c1,i)*C1(c2,j)*C1(c3,k)*C1(c4-1,a[0]-f1-1);
					g[3][1]+=C1(c1,i)*C1(c2,j)*C1(c3,k)*C1(c4-1,a[0]-f1);
				}
			}
		}
	}
	For(i,1,m){
		if(s[0][i]!=s[1][i] && s[0][i]!=s[2][i]){
			ans+=max(g[0][0],g[0][1]);
			if(g[0][0]>=g[0][1]){
				if(s[0][i]=='T') printf("T");
				else printf("F");
			}else{
				if(s[0][i]=='F') printf("T");
				else printf("F");
			}
		}else if(s[1][i]!=s[0][i] && s[1][i]!=s[2][i]){
			ans+=max(g[1][0],g[1][1]);
			if(g[1][0]>=g[1][1]){
				if(s[1][i]=='T') printf("T");
				else printf("F");
			}else{
				if(s[1][i]=='F') printf("T");
				else printf("F");
			}
		}else if(s[2][i]!=s[1][i] && s[0][i]!=s[2][i]){
			ans+=max(g[2][0],g[2][1]);
			if(g[2][0]>=g[2][1]){
				if(s[2][i]=='T') printf("T");
				else printf("F");
			}else{
				if(s[2][i]=='F') printf("T");
				else printf("F");
			}
		}else{
			ans+=max(g[3][0],g[3][1]);
			if(g[3][0]>=g[3][1]){
				if(s[0][i]=='T') printf("T");
				else printf("F");
			}else{
				if(s[0][i]=='F') printf("T");
				else printf("F");
			}
		}
	}
	fenshu(ans,sum);
}

int main()
{
    //freopen("mex.in","r",stdin);
    //freopen("mex.out","w",stdout);
    For(i,0,129){
    	C[i][0]=1;
    	For(j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    T=read();
    For(i,1,T) sol(i);
   	return 0;
}
/*

*/
```

---

