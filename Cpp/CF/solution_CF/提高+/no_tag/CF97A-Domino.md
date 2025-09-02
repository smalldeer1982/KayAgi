# Domino

## 题目描述

Little Gennady was presented with a set of domino for his birthday. The set consists of $ 28 $ different dominoes of size $ 2×1 $ . Both halves of each domino contain one digit from $ 0 $ to $ 6 $ .

`0-0 0-1 0-2 0-3 0-4 0-5 0-6<br></br>1-1 1-2 1-3 1-4 1-5 1-6<br></br>2-2 2-3 2-4 2-5 2-6<br></br>3-3 3-4 3-5 3-6<br></br>4-4 4-5 4-6<br></br>5-5 5-6<br></br>6-6<br></br>`The figure that consists of $ 28 $ dominoes is called magic, if it can be fully covered with $ 14 $ non-intersecting squares of size $ 2×2 $ so that each square contained four equal numbers. Every time Gennady assembles a magic figure, some magic properties of the set appear — he wins the next contest. Gennady noticed that he can't assemble a figure that has already been assembled, otherwise someone else wins the contest.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97A/3c9837941c4e8b07b4c482dcea75feb699170d3b.png)Gennady chose a checked field of size $ n×m $ and put there rectangular chips of sizes $ 1×2 $ and $ 2×1 $ . Each chip fully occupies exactly two neighboring squares of the field. Those chips do not overlap but they can touch each other. Overall the field has exactly $ 28 $ chips, equal to the number of dominoes in the set. Now Gennady wants to replace each chip with a domino so that a magic figure appeared as a result. Different chips should be replaced by different dominoes. Determine in what number of contests Gennady can win over at the given position of the chips. You are also required to find one of the possible ways of replacing chips with dominoes to win the next Codeforces round.

## 样例 #1

### 输入

```
8 8
.aabbcc.
.defghi.
kdefghij
klmnopqj
.lmnopq.
.rstuvw.
xrstuvwy
xzzAABBy
```

### 输出

```
10080
.001122.
.001122.
33440055
33440055
.225566.
.225566.
66113344
66113344
```

# 题解

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF97A)

作为一个2013的题，当时的正解大概还要继续剪枝，但是现在仗着CF机子快我暴力搜480ms 就草过去了这道题。

题意：给定 $28$ 块 $1\,\times2$ 的骨牌和一个棋盘（不是矩形）。这个棋盘有 $56$ 个格子。且可以恰好被 $14$ 个 $2\,\times 2$ 的纸片不重叠地覆盖。容易发现纸片的位置是唯一的。要求利用所有骨牌填满这个棋盘（每个恰好用一次），且满足一个纸片内 $4$ 个格子的颜色是相同的。输出方案数与任意一组解。

观察到题目数据范围很小，这启发我们爆搜。但是样例就有一万多组解，如果一组一组搜怎么剪也肯定会 TLE.

一个显然的优化是，从爆搜骨牌的排列，转变成爆搜 $14$ 个纸片的颜色。这样复杂度就从 $28!$ 变成了 $14!$. 但是依旧不可行。

但是注意到题目给定的骨牌其实就像完全图，有很良好的**轮换性质**。假设我们找到出了一组解，实际上，根据这个性质，一共可以找到 $7!$ 解。

举个例子：如果我 $6$ 张纸片搜出来是 $1,2,1,3,2,3$ 为一组解。那么 $2,3,2,1,3,1$ 也是一组合法的解。事实上，我们任意交换两对四个纸片的颜色，依旧是一组解。上例中，只要第 $1$ 张和第 $3$ 张，第 $2$ 张和第 $5$ 张，第 $4$ 张和第 $6$ 张颜色相同（当然这三对之间不能有两对颜色相同否则违反题意）就是合法的解，并不需要考虑具体的颜色。

思考唯一性：即是否会有状态 $A,B$ 都能置换出 $C$，同时 $A,B$ 不能相互置换。如果有，那么就会重复统计。显然是不会有的。

那么我们考虑用什么状态 $A$ 去代表这一共 $7!=5040$ 个状态。这个状态定义得简单，而且还要便于搜索。这启发我们让代表状态 $A$ 中，第一次出现颜色 $1,2,3,...,7$ 的位置**递增**。此时就可以爆搜了。

由于这个 sol 没有进一步的剪枝（指我不会），所以注意常数问题带来的时间效率影响。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=35,next_x[4]={1,0,-1,0},next_y[4]={0,1,0,-1},BASE=7*6*5*4*3*2*1;
char s[MAXN][MAXN],ret[MAXN][MAXN];
int n,m,tot,ans;
int tag[MAXN][MAXN],rest[MAXN],color[MAXN],state[MAXN][MAXN],cnt[MAXN][MAXN];
pi p[MAXN]; //每个2*2纸片的左上角 
pi over[MAXN][MAXN]; //骨牌的另外一端
void check(){
	rep(i,1,n)rep(j,1,m)state[i][j]=color[tag[i][j]];
	rep(i,1,7){rep(j,i,7)cnt[i][j]=0;}
	rep(i,1,n){
		rep(j,1,m){
			if(s[i][j]=='.')continue;
			int x=i,y=j,x2=over[x][y].fr,y2=over[x][y].se;
			cnt[Min(state[x][y],state[x2][y2])][Max(state[x][y],state[x2][y2])]++;
		}
	}
	rep(i,1,7)rep(j,i,7)if(cnt[i][j]!=2)return;
	ans++;
	if(ans==1){
		rep(i,1,n)rep(j,1,m){
			if(s[i][j]=='.')ret[i][j]='.';
			else ret[i][j]=state[i][j]-1+'0';
		}
	}
} 
void dfs(int u,int r){
	//当前要么选颜色r，要么从[1,r)里选一个 
	if(u==15){
		//检验 
		check();
		return;
	}
	rep(c,1,r-1){
		if(!rest[c])continue;
		color[u]=c;rest[c]--;
		dfs(u+1,r);rest[c]++;
	}
	if(r<=7){
		color[u]=r;rest[r]--;
		dfs(u+1,r+1);rest[r]++;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)rep(j,1,m)scanf(" %c",&s[i][j]);
	rep(i,1,n){
		rep(j,1,m){
			if(s[i][j]=='.')continue;
			rep(k,0,3){
				int cx=i+next_x[k],cy=j+next_y[k]; 
				if(s[cx][cy]==s[i][j])over[i][j]=mp(cx,cy);
			}
			if(tag[i][j])continue;tot++;
			p[tot]=mp(i,j);tag[i][j]=tag[i+1][j]=tag[i][j+1]=tag[i+1][j+1]=tot;
		}
	}
	rep(i,1,7)rest[i]=2;
	dfs(1,1);
	printf("%lld\n",(ll)ans*BASE);
	rep(i,1,n){
		rep(j,1,m)printf("%c",ret[i][j]);
		printf("\n");
	}
	return 0;
}

```


---

## 作者：wosile (赞：0)

cftm 的题解中提到直接搜每个 Domino 取 $28$ 种中的哪一种过不去，需要按纸片的顺序搜，但其实按照 Domino 的顺序一个一个搜也是可以过的。

首先注意到 $14$ 个纸片位置是固定的，所以本质不同的解非常少，大部分解都来自不同数字间的轮换（比如样例实际上只有两组本质不同的解）。

然后即使你不考虑这个轮换，直接对着不同数字硬搜只在途中排除已经不合法的情况（某种数字用了超过两次，或者同一个纸片出现两种数字）也是能过的，但是需要考虑以下几个优化：

- 若一个 Domino 两端所在的纸片位置上的数字都已经确定，则不枚举这个 Domino 是什么（已经完全确定）。

- 若一个 Domino 一端所在的纸片位置上的数字已经确定，则只枚举剩下一端的数字。

注意以上两个优化并不是剪枝，因为并没有减小搜索树，只是在死路的最后一步做了优化。

然后此时已经可以跑到一个比较合理的时间了（0.4 s 左右），但是还是过不去，我们只需要捡回这题的对称性，不枚举第一个 Domino 取什么，如果两端在同一块内就取 `0-0` 然后把答案数乘 $7$，不在同一块内就再额外加上取 `0-1` 的答案计数乘 $21$，后面的每个 Domino 照常搜即可。

细节较多，详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[35][35];
int n,m;
int vis[35][35];// 其实不是 vis，其实是记录当前位置是哪块
int col[35];// 块上的数字
int ccnt[35];// 数字的使用次数
int cvis[10][10];// Domino 是否被使用过
int px1[35],px2[35],py1[35],py2[35];// Domino 的位置
int ans[35][35],tot;
int dfs(int x){
    if(x>28){
        if(tot==0){
            for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)ans[i][j]=col[vis[i][j]];
            tot=1;
        }
        return 1;
    }
    int s1=vis[px1[x]][py1[x]];
    int s2=vis[px2[x]][py2[x]];
    int c1=col[s1];
    int c2=col[s2];
    int sum=0;
    if(c1>0 && c2>0){
        // 两端已确定
        if(!cvis[c1][c2]){
            cvis[c1][c2]=cvis[c2][c1]=1;
            sum+=dfs(x+1);
            cvis[c1][c2]=cvis[c2][c1]=0;
        }
        return sum;
    }
    if(c1>0){
        // 一端已确定
        // s1!=s2
        for(int j=1;j<=7;j++)if(!cvis[c1][j] && ccnt[j]<=1){
            col[s2]=j;
            cvis[c1][j]=cvis[j][c1]=1;
            ccnt[j]++;
            sum+=dfs(x+1);
            col[s2]=0;
            ccnt[j]--;
            cvis[c1][j]=cvis[j][c1]=0;
        }
        return sum;
    }
    if(c2>0){
        // 另一端已确定
        for(int i=1;i<=7;i++)if(!cvis[c2][i] && ccnt[i]<=1){
            if(ccnt[i]>1)continue;
            col[s1]=i;
            cvis[c2][i]=cvis[i][c2]=1;
            ccnt[i]++;
            sum+=dfs(x+1);
            col[s1]=0;
            ccnt[i]--;
            cvis[c2][i]=cvis[i][c2]=0;
        }
        return sum;
    }
    else if(s1==s2){
        // 两端未确定，同一块
        if(x==1){
            // 第一个 domino，利用对称性首特化
            col[s1]=col[s2]=1;
            cvis[1][1]=1;
            ccnt[1]++;
            return dfs(2)*7;
        }
        for(int i=1;i<=7;i++)if(ccnt[i]<=1 && !cvis[i][i]){
            col[s1]=col[s2]=i;
            cvis[i][i]=1;
            ccnt[i]++;
            sum+=dfs(x+1);
            col[s1]=col[s2]=0;
            ccnt[i]--;
            cvis[i][i]=0;
        }
        return sum;
    }
    else{
        // 两端未确定，不同块
        if(x==1){
            // 第一个 domino，利用对称性首特化
            col[s1]=col[s2]=1;
            cvis[1][1]=1;
            ccnt[1]++;
            sum+=dfs(2)*7;
            col[s2]=2;
            cvis[1][1]=0,cvis[1][2]=cvis[2][1]=1;
            ccnt[2]++;
            return sum+dfs(2)*21;
        }
        for(int i=1;i<=7;i++)if(ccnt[i]<=1)for(int j=1;j<=7;j++)if(!cvis[i][j] && ccnt[j]<=1){
            col[s1]=i;
            col[s2]=j;
            cvis[i][j]=cvis[j][i]=1;
            ccnt[i]++;
            ccnt[j]++;
            sum+=dfs(x+1);
            col[s1]=col[s2]=0;
            ccnt[i]--;
            ccnt[j]--;
            cvis[i][j]=cvis[j][i]=0;
        }
        return sum;
    }
    return 1027;
}
int main(){
    scanf("%d%d",&n,&m);

    for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(s[i][j]!='.'){
            if(!vis[i][j]){
                ++cnt;
                vis[i][j]=vis[i+1][j]=vis[i][j+1]=vis[i+1][j+1]=cnt;
            }
            int id;
            if(s[i][j]>='a')id=s[i][j]-'a'+1;
            else id=s[i][j]-'A'+27;
            if(!px1[id]){
                px1[id]=i,py1[id]=j;
            }
            else{
                px2[id]=i,py2[id]=j;
            }
        }
    }
    printf("%d\n",dfs(1));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(ans[i][j])printf("%d",ans[i][j]-1);
            else printf(".");
        }
        printf("\n");
    }
    return 0;
	// quod erat demonstrandum
}
```

---

