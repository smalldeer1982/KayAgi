# [ARC005D] 連射王高橋君

## 题目描述

终于到达鱼屋的高桥君没带多少钱，这样就有些东西不能买，决定向店主询问价格。但店主年老，听力不好，听不见高桥君的声音。没有办法的高桥君决定使用旁边的计算器，把价格打在上面。

但令人困扰的事情是，高桥君不小心把计算器摔了，一些按键摔坏了。计算器有0-9、+和=共12个按键，0、1、+、=四个按键是不会坏的，其余的按键都有坏掉的可能性。

例如，0、1、2、+、=没坏的时候，向店主传达11的方法有以下几种：

1+1+1+1+1+1+1+1+1+1+1=

2+2+2+2+2+1=

11

1+2+1+2+1+1+1+2=

10+1=

+和=有以下的用法：

+只能用于数字之间。

在使用了+的时候，最后需要用=，没有使用+的话不需要使用=。

另外，由于这个鱼屋的店主脾气不大好，需要尽快的打出来避免他生气。所以需要按按钮的次数尽可能的少。之前举例的情况，只按两次按钮的11的时候，按按钮的次数是最少的。

需要在按按钮次数最少的情况下，利用计算器上没有坏的按钮表示出价格。不论输出结果的顺序（若1+2=是正确的，2+1=也是正确的）。

# 题解

## 作者：PosVII (赞：3)

**前言**

------------

CSP2021 前的题解。

$rp++$

**思路**

------------

看到输出序列，不难想到动态规划实现。即 $dp_i$ 表示凑出 $i$ 这个数字所需要的最少的字符。

而我们可以发现动态规划会有两个缺陷：

1. 空间太大，足足 $10^{18}$，因此不可行。 
1. 难以实现，直接DP不能存储方案

对于第二点，我们可以使用记忆化搜索等效替代，但空间的优化需要我们进行思考。如果是学习了数位DP的同学，肯定发现这道题和数位DP都有一个共同点：需要的数字都太大，我们无法直接存储或进行DP。如果是数位DP，我们会存储下当前位数和上一位的数字。那么我们同样可以将这个思路代入这道题。

于是有对于 $dp_{i,j}$，它表示当我们在对第 $i$ 位进行计算时当前位的数字之和为 $j$ 时的最短长度。 

不难发现，我们最多使用 $10$ 个数字就可以表达一个数。因此 $j < 100$。

但是，每个数并不只有一位非零，不能一用就抛弃，那么我们新增状态 $k$ 表示之前已经有 $k$ 个数字了，这样我们就可以在不创建新的数字的情况下做出贡献。同时，我们可能已经在当前位使用了一些数字，所以第四个状态也出现了。

那么空间与时间上就完全可行了，相信输出序列对大家并不难。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
int dp[20][100][12][12];//在看第i位的时候，你还需要凑j，之前已有t个数字，当前位最多有k个没有花费时的最大长度。
int tway[12][20],way[12][20];
int num[20],n,len,ans=INT_MAX;
bool vis[10];
void dfs(int dep,int sum,int free,int u,int res) {
	if(dep==n+1) {
		if(sum!=0) return;
		if(ans>res-(free==1)) {
			len=free;
			ans=res-(free==1);
			for(int i=1;i<=len;++i) {
				for(int j=1;j<=n;++j) {
					way[i][j]=tway[i][j];
				}
			}
		}
		return;
	}
	if(free>=10) return;
	if(dp[dep][sum][free][u]<=res) return;
	dp[dep][sum][free][u]=res;
	for(int i=0;i<=9;++i) {
		if(i>sum) break;
		if(vis[i]) {
			int las=sum-i;
			if(las<10) {
				if(u==0) {
					tway[free+1][dep]=i;
					dfs(dep+1,las*10+num[dep+1],free+1,free+1,res+n-dep+2);
					tway[free+1][dep]=0;
				}
				else {
					tway[u][dep]=i;
					dfs(dep+1,las*10+num[dep+1],free,free,res);
					tway[u][dep]=0;
				}
			}
			if(u==0) {
				tway[free+1][dep]=i;
				dfs(dep,las,free+1,0,res+n-dep+2);
				tway[free+1][dep]=0;
			}
			else {
				tway[u][dep]=i;
				dfs(dep,las,free,u-1,res);
				tway[u][dep]=0;
			}
		}
	}
}
char str[20]; 
long long tar;
int main() {
	memset(dp,127,sizeof(dp)); 
	cin>>str+1;
	for(int i=strlen(str+1);i>=1;--i) vis[str[i]-'0']=1;
	scanf("%lld",&tar);
	while(tar) {
		num[++n]=tar%10;
		tar/=10;
	}
	for(int i=1;i<=n/2;++i) swap(num[i],num[n-i+1]);
	dfs(1,num[1],0,0,0);
	for(int i=1;i<len;++i) {
		bool fl=0;
		for(int j=1;j<=n;++j) {
			if(!fl&&!way[i][j]) continue;
			fl=1;
			printf("%d",way[i][j]);
		}
		printf("+");
	}
	bool fl=0;
	for(int j=1;j<=n;++j) {
		if(!fl&&!way[len][j]) continue;
		fl=1;
		printf("%d",way[len][j]);
	}
	if(len!=1) printf("=\n");
	return 0;
} 
```

---

## 作者：Doveqise (赞：3)

一道搜索题（跟前两道题完全不是一个难度啊QAQ）  
这个搜索写到我虚（还是太虚了）  
刚开始以为是背包OwO  
吹爆这道题！  
两遍dfs emmm...  
按题意写搜索就好（才不是懒得写注释了呢）  
（其实这个代码~~不~~太难看）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int num[20],len,f[15][15][95][20],ava[10],anslen=inf,anscnt;
char s[10];
long long price,pw[20],ansnum[15];
int dfs1(int cnt,int dn,int sum,int ps){
	if(~f[cnt][dn][sum][ps])return f[cnt][dn][sum][ps];
	if(ps>=len)return f[cnt][dn][sum][ps]=(sum==0?0:inf);
	if(dn>=cnt)return f[cnt][dn][sum][ps]=(num[ps]==sum%10?dfs1(cnt,0,sum/10,ps+1):inf);
	int res=inf;
	for(int i=0;i<=9;i++)if(ava[i])res=min(res,dfs1(cnt,dn+1,sum+i,ps)+1);
	if(dn)res=min(res,dfs1(dn,dn,sum,ps));
	return f[cnt][dn][sum][ps]=res;
}//dfs找最小位数
void dfs2(int cnt,int dn,int sum,int ps){
	if(ps>=len)return;
	if(dn>=cnt){dfs2(cnt,0,sum/10,ps+1);return;}
	int now=f[cnt][dn][sum][ps];
	for(int i=0;i<=9;i++)if(ava[i]&&f[cnt][dn+1][sum+i][ps]+1==now){
		ansnum[dn]+=1ll*i*pw[ps],dfs2(cnt,dn+1,sum+i,ps);return;}
	dfs2(dn,dn,sum,ps);//dfs找方案
}
int main(){
	scanf("%s%lld",s,&price);//读入
	int leng=strlen(s);//数字个数
	for(int i=0;i<=leng;i++)ava[s[i]-'0']=1;//能用的数字
	while(price)num[len++]=price%10,price/=10;//price位数
	memset(f,-1,sizeof(f));
	for(int i=1;i<=10;i++){
		int now=(i==1?0:i)+dfs1(i,0,0,0);
		if(now<anslen)anslen=now,anscnt=i;//检验答案最优性
	}
	pw[0]=1;
	for(int i=1;i<=len;i++)pw[i]=pw[i-1]*10;
	dfs2(anscnt,0,0,0);if(anscnt==1)printf("%lld",ansnum[0]);
	else for(int i=0;i<=anscnt-1;i++){printf("%lld",ansnum[i]);printf("%c",(i+1)==anscnt?'=':'+');}//输出
	puts("");/*万恶换行*/return 0;
}

```


---

