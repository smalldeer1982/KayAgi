# [CCC 2008 J5/S5] Nukit

## 题目描述

加拿大的两位顶尖核科学家，Patrick 和 Roland，刚刚完成了世界上第一个核裂变反应堆的建造。现在，他们的工作是每天坐在反应堆前操作它。自然地，在这样做了一段时间后，他们有些无聊，因此发生了两件事。首先，他们现在可以控制反应堆内发生的个别反应。其次，为了打发时间，他们发明了一种叫做 Nukit 的新游戏。

在 Nukit 的开始阶段，反应堆中放入了一些粒子。玩家轮流进行操作，Patrick 总是先走。当轮到一个玩家操作时，他们必须选择一些剩余的粒子来形成一个可能的反应。然后这些粒子被销毁。最终，粒子会变得如此之少，以至于无法形成任何反应；此时，第一个无法在其回合中形成反应的人输掉比赛。

在我们的宇宙中，你可以假设只有 $4$ 种类型的粒子：`A`，`B`，`C`，`D`。每个反应都是可以在单个回合中销毁的粒子列表。五种反应是：

1. `AABDD`

2. `ABCD`

3. `CCD`

4. `BBB`

5. `AD`

例如，第一个反应 `AABDD` 表示可以在一个回合中同时销毁两个 `A`，一个 `B` 和两个 `D` 粒子。

事实证明，无论反应堆中最初有多少粒子，Patrick 或 Roland 中总有一个人有完美的获胜策略。我们所说的玩家 $X$ 有完美的获胜策略，意味着无论另一个玩家做什么，玩家 $X$ 都可以通过仔细选择反应来获胜。

例如，如果反应堆最初有一个 `A`，五个 `B` 和三个 `D` 粒子，那么 Roland 有以下完美的获胜策略：“如果 Patrick 最初形成反应 `BBB`，那么随后形成反应 `AD`；如果 Patrick 最初形成反应 `AD`，那么随后形成反应 `BBB`。”（策略有效，因为无论哪种方式，在 Patrick 的第二个回合中，剩余的粒子不足以形成任何反应。）

给定反应堆中每种类型的粒子的初始数量，你能找出谁有完美的获胜策略吗？

## 说明/提示

样例输出的部分解释：

第一个输出发生是因为 Patrick 立即输掉，因为他无法形成任何反应。（Roland 的完美获胜策略是“什么都不做。”）

第二个输出发生是因为 Patrick 有完美的获胜策略“形成反应 ABCD”，这使得 Roland 在他的第一个回合中输掉。

第三个输出在问题陈述中已解释。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6
0 2 0 2
1 3 1 3
1 5 0 3
3 3 3 3
8 8 6 7
8 8 8 8```

### 输出

```
Roland
Patrick
Roland
Roland
Roland
Patrick```

# 题解

## 作者：ivyjiao (赞：2)

其实题面少了一句话：假设两人都足够聪明，我们给它加上。

首先，在博弈中，我们明确三个性质：

- 如果一个状态的后继有一个必败状态，则该状态为必胜状态。
- 如果一个状态的后继全都是必胜状态，则该状态为必败状态。
- 不能再取的状态为必败状态（即：不能再取的状态的后继全都是必胜状态）。

一般的博弈论题都是可以通过这两条从 $(0,0)$ 递推出所有状态的，然而这道题每个状态不仅给了四个点，还有五种转移式，根本无法转移。但是数据范围很小，所以我们考虑爆搜加记忆化。

~~不知道为什么清空 dp 数组的时候不能用 memset，我在这里寄了十分钟~~。

根据以上性质，我们可以写出这样一份代码：

```
#include<bits/stdc++.h>
using namespace std;
int t,a,b,c,d,dp[31][31][31][31];
bool dfs(int a,int b,int c,int d){
    if(a<0||b<0||c<0||d<0) return 1;//不能再取的状态的后继全都是必胜状态
    if(dp[a][b][c][d]!=-1) return dp[a][b][c][d];
    if(dfs(a-2,b-1,c,d-2)&&dfs(a-1,b-1,c-1,d-1)&&dfs(a,b,c-2,d-1)&&dfs(a,b-3,c,d)&&dfs(a-1,b,c,d-1)) dp[a][b][c][d]=0;//如果一个状态的后继全都是必胜状态，则该状态为必败状态。
    else dp[a][b][c][d]=1;//如果一个状态的后继有一个必败状态，则该状态为必胜状态。
    return dp[a][b][c][d];
}
int main(){
    cin>>t;
    while(t--){
        for(int i=0;i<=30;i++) for(int j=0;j<=30;j++) for(int k=0;k<=30;k++) for(int l=0;l<=30;l++) dp[i][j][k][l]=-1;
        cin>>a>>b>>c>>d;
        if(dfs(a,b,c,d)) cout<<"Patrick"<<endl;
        else cout<<"Roland"<<endl;
    }
}
```

---

## 作者：Tjaweiof (赞：1)

# P9862 题解
[题目传送门](https://www.luogu.com.cn/problem/P9862)

解法：记忆化搜索

定义一个数组 $dp$，$dp_{i,j,k,l}$ 用来存当 $a=i,b=j,c=k,d=l$ 时谁会赢，为 $1$ 时表示 Patrick 赢了，为 $0$ 时表示 Roland 赢了。

通过调用一个递归函数，我们得出了以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, b, c, d, dp[31][31][31][31];
void dfs(int a, int b, int c, int d){
    if (a < 0 || b < 0 || c < 0 || d < 0){
        return;
    }
    if (dp[a][b][c][d] != 0x3f3f3f3f){
        return;
    }
    dfs(a - 2, b - 1, c, d - 2);
    dfs(a - 1, b - 1, c - 1, d - 1);
    dfs(a, b, c - 2, d - 1);
    dfs(a, b - 3, c, d);
    dfs(a - 1, b, c, d - 1);
    if (dp[a - 2][b - 1][c][d - 2] && dp[a - 1][b - 1][c - 1][d - 1] && dp[a][b][c - 2][d - 1] && dp[a][b - 3][c][d] && dp[a - 1][b][c][d - 1]){
        dp[a][b][c][d] = false;
    } else {
        dp[a][b][c][d] = 1;
    }
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    while (n--){
        memset(dp, 0x3f3f3f3f, sizeof dp);
        cin >> a >> b >> c >> d;
        dfs(a, b, c, d);
        if (dp[a][b][c][d]){
            cout << "Patrick" << endl;
        } else {
            cout << "Roland" << endl;
        }
    }
    return 0;
}
```

提交上去一看，为什么会全部 RE 呢？

问题出在 `dfs` 函数的第三个 `if` 语句内，因为 $a$ 有可能小于 $2$（不只是这一种，这里只是例举了一种情况），那么 $a-2$ 就是负数。为此做出一些调整（详见代码），修正后得到 AC 代码。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, b, c, d, dp[32][32][32][32];
void dfs(int a, int b, int c, int d){
    if (a < 0 || b < 0 || c < 0 || d < 0){
        return;
    }
    if (dp[a][b][c][d] != 0x3f3f3f3f){
        return;
    }
    dfs(a - 2, b - 1, c, d - 2);
    dfs(a - 1, b - 1, c - 1, d - 1);
    dfs(a, b, c - 2, d - 1);
    dfs(a, b - 3, c, d);
    dfs(a - 1, b, c, d - 1);
    if (dp[a - 2 >= 0 ? a - 2 : 31][b - 1 >= 0 ? b - 1 : 31][c][d - 2 >= 0 ? d - 2 : 31] && dp[a - 1 >= 0 ? a - 1 : 31][b - 1 >= 0 ? b - 1 : 31][c - 1 >= 0 ? c - 1 : 31][d - 1 >= 0 ? d - 1 : 31] && dp[a][b][c - 2 >= 0 ? c - 2 : 31][d - 1 >= 0 ? d - 1 : 31] && dp[a][b - 3 >= 0 ? b - 3 : 31][c][d] && dp[a - 1 >= 0 ? a - 1 : 31][b][c][d - 1 >= 0 ? d - 1 : 31]){
        dp[a][b][c][d] = 0;
    } else {
        dp[a][b][c][d] = 1;
    }
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    while (n--){
        memset(dp, 0x3f3f3f3f, sizeof dp);
        cin >> a >> b >> c >> d;
        dfs(a, b, c, d);
        if (dp[a][b][c][d]){
            cout << "Patrick" << endl;
        } else {
            cout << "Roland" << endl;
        }
    }
    return 0;
}
```
**此代码时间复杂度 $O(nabcd)$，空间复杂度 $O(abcd)$，完美过关！**

---

## 作者：rnf5114 (赞：1)

此题初看是博弈论，实际上只是一个记忆化搜索题，只不过用到了一点点博弈论的思想：如果我想赢，那么当前我的手牌经过操作后一定可以得到让对手必输的状态。很容易的，想到记忆化搜索。

首先记录下来一次都打不出去的所有手牌情况，然后往上逆推即可。

## Code

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int vis[10][10][10][10],n,s;
int a[10][10];
string ans[2];
struct node{
	int a,b,c,d;
}b[100010];
bool check(int a1,int b,int c,int d){
	for(int i=1;i<=5;i++){
		int tmpa=a1-a[i][1],tmpb=b-a[i][2],tmpc=c-a[i][3],tmpd=d-a[i][4];
		if(tmpa>=0&&tmpb>=0&&tmpc>=0&&tmpd>=0)
			return false;
	}
	return true;
}
int dfs(int a1,int b,int c,int d){
	if(vis[a1][b][c][d]==1||!vis[a1][b][c][d])
		return vis[a1][b][c][d];
	for(int i=1;i<=5;i++){
		int tmpa=a1-a[i][1],tmpb=b-a[i][2],tmpc=c-a[i][3],tmpd=d-a[i][4];
		if(tmpa>=0&&tmpb>=0&&tmpc>=0&&tmpd>=0){
			int tmp=dfs(tmpa,tmpb,tmpc,tmpd);
			if(tmp==1)
				vis[a1][b][c][d]=0;
			else{
				if(vis[a1][b][c][d]!=0)
					vis[a1][b][c][d]=1;
			}
		}
	}
	return vis[a1][b][c][d];
}
int main(){
	cin>>n;
	ans[0]="Patrick";
	ans[1]="Roland";
	a[1][1]=2;
	a[1][2]=1;
	a[1][4]=2;
	a[2][1]=1;
	a[2][2]=1;
	a[2][3]=1;
	a[2][4]=1;
	a[3][3]=2;
	a[3][4]=1;
	a[4][2]=3;
	a[5][1]=1;
	a[5][4]=1;
	memset(vis,127,sizeof vis);
	for(int i=0;i<=8;i++){
		for(int j=0;j<=8;j++){
			for(int k=0;k<=8;k++){
				for(int l=0;l<=8;l++){
					if(check(i,j,k,l)){
						s++;
						b[s].a=i;
						b[s].b=j;
						b[s].c=k;
						b[s].d=l;
						vis[i][j][k][l]=1;
					}
				}
			}
		}
	}
	for(int i=0;i<=8;i++){
		for(int j=0;j<=8;j++){
			for(int k=0;k<=8;k++){
				for(int l=0;l<=8;l++){
					dfs(i,j,k,l);
				}
			}
		}
	}
	while(n--){
		int q,w,e,r;
		cin>>q>>w>>e>>r;
		cout<<ans[vis[q][w][e][r]]<<endl;
	} 
    return 0;
}


/*

       ┏┓　　　┏┓
     ┏┛┻━━━┛┻┓
     ┃　　　　　　　┃
     ┃　　　━　　　┃
     ┃　┳┛　┗┳　┃
     ┃　　　　　　　┃
     ┃　　　┻　　　┃
     ┃　　　　　　　┃
     ┗━┓　　　┏━┛Codes are far away from bugs with the animal protecting
         ┃　　　┃    神兽保佑,代码无bug
         ┃　　　┃
         ┃　　　┗━━━┓
         ┃　　　　　 ┣┓
         ┃　　　　 ┏┛
         ┗┓┓┏━┳┓┏┛
           ┃┫┫　┃┫┫
           ┗┻┛　┗┻┛     ○|￣|_

*/

```


---

## 作者：Laoda_Bryant (赞：0)

## 思路
记忆化搜索。  
因为两个人都很聪明，所以问的其实是谁有**必胜**策略。  
这里设 $dp_{a,b,c,d}$ 表示为当局面为 $a,b,c,d$ 时 Patrick 是否有必胜策略，是为 $1$，不是为 $0$。  
那么可以得到：
* 当 $dp_{a-2,b-1,c,d-2}$、$dp_{a-1,b-1,c-1,d-1}$、$dp_{a,b-3,c,d}$ 和 $dp_{a-1,b,c,d-1}$ 都为必胜状态时，则为必败状态。因为不论你用哪种方法去取，对手都能找出一种必胜的方案赢你。
* 否则当这四种方案中只要有一种为必败状态时，则为必胜状态。因为你可以用那一种方案来嬴对方。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,b,c,d,dp[50][50][50][50];
int dfs(int a,int b,int c,int d){
	if(a<0||b<0||c<0||d<0) return 1;//取不了，对手必胜。
	if(dp[a][b][c][d]==-1){
		if(dfs(a-2,b-1,c,d-2)&&dfs(a-1,b-1,c-1,d-1)&&dfs(a,b,c-2,d-1)&&dfs(a,b-3,c,d)&&dfs(a-1,b,c,d-1)) dp[a][b][c][d]=0; //四种方法都对手都必胜，则必败。
		else dp[a][b][c][d]=1;//反之必胜。
	}
	return dp[a][b][c][d];
}
int main(){
	for(int a=0;a<=30;a++){
		for(int b=0;b<=30;b++){
			for(int c=0;c<=30;c++){
				for(int d=0;d<=30;d++){
					dp[a][b][c][d]=-1;
				}
			}
		}
	}
	cin>>T;
	while(T--){
		cin>>a>>b>>c>>d;
		if(dfs(a,b,c,d)) puts("Patrick");
		else puts("Roland");
	}
	return 0;
}
```

---

## 作者：zbzbzzb (赞：0)

这道题的形式很容易看出是博弈论，但是并不需要，只需一个记忆化搜索。

因为是博弈论，所以我们做题时假定他们都足够聪明。

我们可以设 $dp_{a,b,c,d}=1$ 时代表 Patrick 必胜。

我们知道：

- 当现在为必胜状态时，下一次所有的情况都是必胜的。

- 当现在为不必胜状态时，下一次所有的情况都不是必胜的。

接下来看代码注释。

### CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d,dp[50][50][50][50];
int dfs(int a,int b,int c,int d){
	if(a<0||b<0||c<0||d<0){//不能继续取，必胜
		return 1;
	}if(dp[a][b][c][d]==-1){
		if(dfs(a-2,b-1,c,d-2)==1&&dfs(a-1,b-1,c-1,d-1)==1&&dfs(a,b,c-2,d-1)==1&&dfs(a,b-3,c,d)==1&&dfs(a-1,b,c,d-1)==1){//全部必胜
			return dp[a][b][c][d]=0;//不必胜
		}else{//没有必胜
			return dp[a][b][c][d]=1;//不必胜
		}
	}else{
		return dp[a][b][c][d];
	}
}int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		memset(dp,-1,sizeof dp);//清空！！
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(dfs(a,b,c,d)==1){//必胜，就是结果为1
			printf("Patrick\n");
		}else{
			printf("Roland\n");
		}
	}return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题目大意：已经说得够清楚了。

[**P9862 [CCC 2008 J5/S5] Nukit 题解**](https://www.luogu.com.cn/problem/P9862)

这是一道**博弈论**题，~~不会有人不知道什么叫博弈论吧~~。如果不知道，我们先介绍一下什么叫博弈论。

其实博弈论就是小学奥数题里的取石子游戏，每人可以取若干个物品，先取完者胜，也可以是报数等变形题。另一种就是 Nim 游戏，具体规则参见 [P2197 【模板】Nim 游戏](https://www.luogu.com.cn/problem/P2197)，不再讲述。

我们步入正题。由于字符个数很小，我们可以记录 $dp_{a,b,c,d,ok}$，其中 $a,b,c,d$ 分别代表每种字符还剩几个。当 $ok=0$ 时，表示 Patrick 取；当 $ok=1$ 时则表示 Roland 取。再来考虑俩人的**必胜策略**。当 $dp_{a,b,c,d,ok}=1$ 时表示 Patrick 有必胜策略；反之则没有。所以我们要求 $dp_{a,b,c,d,ok}$ 是否等于 $1$ 。我们又知道当一个状态为必胜状态时，下一步能够产生的所有状态**都是必胜状态**。当一个状态不必胜时，下一步能产生的状态中**不必胜**。我们知道了这个，在分类讨论，代码就好写了。

Tip：配合记忆化搜索味道更佳哦！

这里是[**代码**](https://www.luogu.com.cn/paste/14ixa962)（~~不会有人只看这里吧……~~）。

---

## 作者：TruchyR (赞：0)

## Part 1 思路
“假设两人都足够聪明。”   
这道题是博弈论练手题。  
注意到 $n\leq 100$，每个字母最多有 $m\leq30$ 个，可以容许 $O(nm^4)$ 的算法通过。  
博弈论有挺多写法的，这里采用了记忆化搜索。  
- 设计状态  
较为显而易见，我们可以设 $f_{a,b,c,d,opt}=\pm 1$ 代表在当前局面，先后/手的回合，谁是必胜的。  
笔者这里在设值为 $1$ 时先手必胜，值为 $-1$ 时后手必胜。  

- 搜索函数   
向下搜索自己的所有操作，如果发现自己必胜，那么这个函数可以直接结束了。  
按照题意一一打上即可。  
  - $\min\{a,b,c,d\}<0$：  
  对方违反了规则，直接返回 $opt$。  
  这个部分在有判断合法性不需要。  
  - $5$ 种操作  
  这部分见代码。  
  
- 主函数  
主函数就没什么好写的了。  
一个细节是这个状态不需要初始化数组，所以复杂度可以降到 $O(m^4)$！  

## Part 2 代码
```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
using namespace std;
const int CHECK=0,FIL=0;int read();
int T,f[35][35][35][35][2];
int gx(int g,int a,int b){
    if(g==1) return max(a,b);
    return min(a,b);
}
int dfs(int a,int b,int c,int d,int g){
    if(a<0||b<0||c<0||d<0) return g;//不合法
    if(f[a][b][c][d][max(0,g)]) return f[a][b][c][d][max(0,g)];//搜索过了
    int res=-g;//五种操作
    res=gx(g,res,dfs(a-2,b-1,c,d-2,-g));
    res=gx(g,res,dfs(a-1,b-1,c-1,d-1,-g));
    res=gx(g,res,dfs(a,b,c-2,d-1,-g));
    res=gx(g,res,dfs(a,b-3,c,d,-g));
    res=gx(g,res,dfs(a-1,b,c,d-1,-g));
    return f[a][b][c][d][max(0,g)]=res;//记忆化结果
}
signed main(){
	FRE freopen(".in","r",stdin);
	FRE freopen(".out","w",stdout);
    T=read();while(T--){//输入+调用+输出
        int a=read();int b=read();
        int c=read();int d=read();
        if(dfs(a,b,c,d,1)>0) printf("Patrick\n");
        else printf("Roland\n");
    }
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```


---

## 作者：__zfy__ (赞：0)

### 思路

普普通通~~非常困难~~的博弈论。

首先看到博弈论，看这题什么决定了它的状态，比如这个题就是如 Patrick 的某一个状态的后继状态是必输的，那么这个状态本身就是必胜的，因为两人都很聪明。这样再结合状态对应的四元组 $(a,b,c,d)$ 与每一个状态的对应转移，也就是比如 Patrick 先手，他就可以把这个必输的状态转移给  Roland，这样 Roland 就是必输的了。反之亦然，如果 Patrick 的后继状态有一个必胜的状态，那 Roland 才是这个必胜的，因为后手可以转移状态。

接着看如何实现找他的后继状态，显然题目中已经给出，我们只需要分类讨论即可。可以使用记忆化搜索来解决，因为记忆化搜索可以记住每一次这状态转移时，看它是不是一个状态的后继状态，如果是，那就看是必胜还是必败，再对当前状态做出判断，必胜状态判断方法如下：

$a \le -1$ $or$ $b \le -1$ $or$ $c \le -1$ $or$ $d \le -1$。

### 代码

```cpp
if(dfs(a-2,b-1,c,d-2)==0) vis[a][b][c][d]=1;
else if(dfs(a-1,b-1,c-1,d-1)==0) vic[a][b][c][d]=1;
else if(dfs(a,b,c-2,d-1)==0) vis[a][b][c][d]=1;
else if(dfs(a,b-3,c,d)==0) vis[a][b][c][d]=1;
else if(dfs(a-1,b,c,d-1)==0) vis[a][b][c][d]=1;
else vis[a][b][c][d]=0;
return vis[a][b][c][d];
```

---

## 作者：Suite_No1_G (赞：0)

很明显的博弈论。

由于字符的个数很小，我们可以考虑记录 $dp_{a,b,c,d,op}$。其中 $a$，$b$，$c$，$d$ 分别代表每种字符还剩几个，$op$ 为 $0$ 表示 Patrick 取，为 $1$ 表示 Roland 取。如果 $dp_{a,b,c,d,op}$ 为 $1$ 表示 Patrick 有必胜策略，为 $0$ 表示无必胜策略。

则要求 $dp_{a,b,c,d,0}$ 是否为 $1$。

然后，我们要知道：

当一个状态为必胜状态时，下一步能够产生的所有状态都是必胜状态。当一个状态不必胜时，下一步能产生的状态中不必胜。

所以，分情况讨论即可。

优化：可以采取记忆化搜索。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=32;
int dp[maxn][maxn][maxn][maxn][2];
//0-> P 1->R

int dfs(int a,int b,int c,int d,int op){
	if (dp[a][b][c][d][op]!=-1) return dp[a][b][c][d][op];
	int find=0;//判断能否操作
	if (a>=2&&b>=1&&d>=2) find=1;
	if (a>=1&&b>=1&&c>=1&&d>=1) find=1;
	if (c>=2&&d>=1) find=1;
	if (b>=3) find=1;
	if (a>=1&&d>=1) find=1;
	
	if (find==0){不能操作的话，当前玩家输
		if (op==0) return dp[a][b][c][d][op]=0;
		else return dp[a][b][c][d][op]=1;
	}
	
	if (op==0){//Patrick
		int flag=0;//只要有状态使得Patrick必胜，则当前状态Patrick必胜
		if (a>=2&&b>=1&&d>=2&&dfs(a-2,b-1,c,d-2,op^1)==1) flag=1;
		if (a>=1&&b>=1&&c>=1&&d>=1&&dfs(a-1,b-1,c-1,d-1,op^1)==1) flag=1;
		if (c>=2&&d>=1&&dfs(a,b,c-2,d-1,op^1)==1) flag=1;
		if (b>=3&&dfs(a,b-3,c,d,op^1)==1) flag=1;
		if (a>=1&&d>=1&&dfs(a-1,b,c,d-1,op^1)==1) flag=1;
		return dp[a][b][c][d][op]=flag;
	}else{//Roland
		int flag=1;//只要有状态使得Patrick不必胜，则当前状态Patrick不必胜
		if (a>=2&&b>=1&&d>=2&&dfs(a-2,b-1,c,d-2,op^1)!=1) flag=0;
		if (a>=1&&b>=1&&c>=1&&d>=1&&dfs(a-1,b-1,c-1,d-1,op^1)!=1) flag=0;
		if (c>=2&&d>=1&&dfs(a,b,c-2,d-1,op^1)!=1) flag=0;
		if (b>=3&&dfs(a,b-3,c,d,op^1)!=1) flag=0;
		if (a>=1&&d>=1&&dfs(a-1,b,c,d-1,op^1)!=1) flag=0;
		return dp[a][b][c][d][op]=flag;
	}
}

int main(){
	int T;
	scanf("%d",&T);
	memset(dp,-1,sizeof(dp));
	
	while (T--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if (dfs(a,b,c,d,0)==1) printf("Patrick\n");
		else printf("Roland\n");
	}
	return 0;
}
```


---

## 作者：xiangyanhao (赞：0)

本题是一个博弈论问题，然而却不需要我们使用 SG 函数，直接暴力即可。

定义：在双方最优策略下，先手必胜的状态为必胜状态，先手必败的状态为必败状态，状态定义为四元组 $(a,b,c,d)$，状态之间的转移在题目描述中已给出。

若一个状态的后继状态中存在必败状态，则该状态为必胜状态（因为该状态下先手可以进行转移把必败状态交给对手），反之为必败状态。这样，我们就能通过记忆化搜索找到状态究竟是必胜状态还是必败状态。为了代码实现上的简便，当 $a<0\operatorname{or}b<0\operatorname{or}c<0\operatorname{or}d<0$ 时，我们定义这一状态为必胜状态，因为这一状态有可能被意外转移到，将其定义为必胜状态可以使其即使意外被转移到也不影响结果。核心代码如下：

```cpp
int vic[35][35][35][35]; //vic存储状态是必胜还是必败，1表示必胜，0表示必败
int dfs(int a,int b,int c,int d){
	if(a<0||b<0||c<0||d<0) return 1;
	if(vic[a][b][c][d]!=-1) return vic[a][b][c][d];
	//枚举每一种转移，看后继是否存在必败状态
	if(dfs(a-2,b-1,c,d-2)==0) vic[a][b][c][d] = 1;
	else if(dfs(a-1,b-1,c-1,d-1)==0) vic[a][b][c][d] = 1;
	else if(dfs(a,b,c-2,d-1)==0) vic[a][b][c][d] = 1;
	else if(dfs(a,b-3,c,d)==0) vic[a][b][c][d] = 1;
	else if(dfs(a-1,b,c,d-1)==0) vic[a][b][c][d] = 1;
	else vic[a][b][c][d] = 0;
	return vic[a][b][c][d];
}
```

最后，只要对每组数据，判断 `dfs(a,b,c,d)==1` 是否成立（是则输出 `Patrick`，否则输出 `Roland`）即可。

---

