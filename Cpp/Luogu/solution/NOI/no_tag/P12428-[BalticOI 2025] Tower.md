# [BalticOI 2025] Tower

## 题目描述

关于托伦斜塔有许多传说。塔的墙壁是一个带有 $N \geq 3$ 个均匀分布的门（换句话说，这些门构成一个正 $N$ 边形的顶点）的圆形结构。门的编号从 0 到 $N - 1$，但顺序是随机的。更多细节请参考评分部分。

其中一个不太为人所知的传说描述了每位新居民必须完成的挑战。挑战的目标是列出所有门，从某一扇门开始，然后沿着圆形（顺时针或逆时针）行走，恰好访问每扇门一次。

这一过程无法直接观察塔楼，而是需要通过提问来获取信息。每次提问的形式如下："给定三扇不同的门 $x$、$y$、$z$，哪对门之间的距离最近：$\{x, y\}$、$\{y, z\}$ 还是 $\{z, x\}$？"。这类问题的回答将给出所有距离最近的门对（在 $\{x, y\}$、$\{y, z\}$ 和 $\{z, x\}$ 中）。距离是指连接两扇门的最短线段的长度。你的任务是编写一个程序，通过少量此类提问来确定门的排列顺序。

### 交互说明

这是一个交互式任务。你需要编写一个程序，通过与交互器进行标准输入输出的交互来解决问题。

在交互开始时，你的程序应从标准输入读取两个整数 $t$ 和 $k$（$1 \leq t \leq 100$，$1 \leq k \leq 12000$），分别表示测试用例的数量和允许的平均提问次数上限。更多信息请参考评分部分。

对于每个测试用例，你的程序应首先从标准输入读取一个整数 $n$（$3 \leq n \leq 500$），表示塔楼中门的数量。

然后，你的程序可以通过以下方式提问：

- 向标准输出写入一行格式为  
  $?\ x\ y\ z$  
  的内容，其中 $x$、$y$ 和 $z$ 是不同的整数（$0 \leq x, y, z \leq n - 1$）。这一行表示一个关于门 $x$、$y$ 和 $z$ 的提问。
- 交互器的响应格式为：  
  $r$  
  $a_1\ b_1$  
  $\vdots$  
  $a_r\ b_r$  
  其中 $r$ 是一个整数（$1 \leq r \leq 3$），表示距离最近的门对数量。每个门对由两个整数 $a_i$ 和 $b_i$（$a_i, b_i \in \{x, y, z\}$ 且 $a_i < b_i$）描述。

一旦确定了门的顺序，你的程序应向标准输出写入一行格式为

$!\ x_0\ x_1\ \dots\ x_{n-1}$

的内容，其中 $x_0, x_1, \ldots, x_{n-1}$ 是题目描述中要求的门的顺序。注意共有 $2n$ 种可能的正确答案，因为你可以从任意一扇门开始，并按任意方向排列。其中任何一种都会被接受。

**请记住，每次提问或回答后，必须使用 `cout.flush()`（或 `fflush(stdout)`，如果使用 `printf`）或 Python 中的 `sys.stdout.flush()` 刷新输出缓冲区。** 否则你的程序可能会因超时而失败。

在向交互器输出答案后，你的程序应立即处理下一个测试用例，或在所有测试用例处理完毕后结束交互。

你的程序不能打开任何文件或使用其他资源。可以使用标准错误流进行调试，但请注意写入该流会消耗时间。

另外请注意，交互器不是自适应的，即每个测试用例中门的初始顺序在交互开始前已固定，不会在交互过程中改变。

## 说明/提示

假设我们只有一个测试用例，$n = 6$，且门的顺序为 $5, 3, 0, 2, 1, 4$。交互过程可能如下：

| 交互器 | 你的程序 | 说明 |
| :---: | :---: | :---: |
| 1 100 |  | $t=1$ 且 $k=100$。 |
| 6 |  | 交互器给出第一个测试用例的门数。 |
|  | ? 0 1 2 | 你的程序询问哪对门距离最近。 |
| 2 |  | 门对 $\{0,2\}$ 和 $\{1,2\}$ 距离最近。 |
| 0 2 |  |  |
| 1 2 |  |  |
|  | ? 4 1 3 | 你的程序询问哪对门距离最近。 |
| 1 |  | 门对 $\{1,4\}$ 距离最近。 |
| 1 4 |  |  |
|  | ? 0 5 1 | 你的程序询问哪对门距离最近。 |
| 3 |  | 门对 $\{0,5\}$、$\{0,1\}$ 和 $\{1,5\}$ 距离最近。 |
| 0 5 |  |  |
| 0 1 |  |  |
| 1 5 |  |  |
|  | ! 4 5 3 0 2 1 | 你的程序正确输出门的顺序。 |

![](https://cdn.luogu.com.cn/upload/image_hosting/cqzay89h.png)

样例解释：上图展示了塔楼墙壁上门的编号。最左边的图片显示了编号为 $0, 1, 2$ 的门形成的三角形，对应你的程序的第一个提问。可以看到，门对 $\{0, 2\}$ 和 $\{1, 2\}$ 距离最近。中间的图片显示了编号为 $1, 4, 3$ 的门形成的三角形，对应第二个提问。显然，门对 $\{1, 4\}$ 距离最近。最右边的图片显示了编号为 $0, 1, 5$ 的门形成的三角形，对应第三个提问。可以看到，所有门对的距离都相等。

注意，序列 $0, 2, 1, 4, 5, 3$ 或 $5, 4, 1, 2, 0, 3$（以及其他几种）在此情况下也是正确答案。

### 评分

本题的评分分为多个子任务。每个子任务仅包含一个测试，该测试包含 $t = 100$ 个测试用例。对于每个测试，你的程序的平均提问次数为所有测试用例的总提问次数除以测试用例数。如果该平均值超过给定子任务的 $k$ 值，则该子任务得分为 $0$。否则，对于子任务 1 至 4，你将获得该子任务的满分。

对于最后一个子任务，你的得分将按以下方式计算。设 $k^*$ 为你的程序实际的平均提问次数，则得分由以下公式给出：

$$\left\lceil 56 \cdot \min \left(1, \frac{12000 - k^*}{7800}\right) \right\rceil$$

这意味着当 $k^*$ 从 12000 降到 4200 时，你的得分将从 0 线性增加到 56。

请注意，如果你的程序在任何测试用例中给出错误答案，无论提问次数多少，该子任务的得分都将为 0。

各子任务的额外约束如下表所示：

| 子任务 | 约束条件 | 分值 |
| :---: | :---: | :---: |
| 1 | $k = 8000, 3 \leq n \leq 9$ | 6 |
| 2 | $k = 4500, 40 \leq n \leq 50$ | 7 |
| 3 | $k = 3000, 90 \leq n \leq 100$ | 9 |
| 4 | $k = 4500, n = 400$，存在正确答案 $x_0, \ldots, x_{n-1}$ 满足 $x_i = i$（$200 \leq i \leq 399$） | 22 |
| 5 | $k = 12000, n = 500$ | 最高 56 |

此外，可以假设每个测试用例的生成方式为：首先从满足子任务约束的所有 $n$ 值中均匀随机选择一个 $n$，然后从满足子任务约束的所有 $n$ 扇门的排列中均匀随机选择一个顺序。

翻译由 DeepSeek V3 完成

# 题解

## 作者：_Ch1F4N_ (赞：1)

很抽象的题目。

首先看到评分标准是所有测试用例的平均次数而不是最大次数与数据随机生成，考虑随机化做法。

对于一个初始的长度为 $n$ 的圆上的 $x,y$，假若我们把其他点全部问一遍，那么就可以把点分为三类，距离 $x$ 较为近的，距离 $y$ 较近的，和距离 $x,y$ 都比较远的。

三类点都构成圆的一段弧，但是第三类点可能构成优弧，这是我们不希望看到的，因为处理优弧上问题时可能出现两个优弧上的点最短路径不在优弧上的情况，考虑合理的选择 $x,y$ 以规避第三类点出现。

不难发现不出现第三类点（或者第三类点只包含一个单独的点）的充要条件是 $dis(x,y) \geq \frac{n}{3}$，也就是我们希望尽可能选较长的弧。

考虑这样一个算法：先随机选取一对 $x,y$，然后依次考虑剩下的点，如果剩下的点 $u$ 与 $x,y$ 询问一次后 $x,y$ 是唯一的最短边，那么就让 $y \gets u$，看上去这个东西很对，写个暴力发现，对于 $n=500$ 的情况，这个东西跑一轮大概只有 $\frac{3}{1000}$ 的概率跑不出符合条件的 $x,y$，而这个题只需要保证平均次数限制，所以这个算法是可以接受的。

实际上问出一组满足条件的 $x,y$ 后，圆会被对等分开（也可能存在 $0 \sim 2$ 个分界点），显然切割出来的都是劣弧，其上两点的最短路径一定全部在劣弧上，故可以使用类似上面的算法继续分治下去，合并弧首先考虑如果询问问出来了分界点，直接把分界点分别拼接在两条弧两侧即可，否则考虑合并两条有序的弧 $L_1,L_2$ 时，先令 $|L_1| \leq |L_2|$，然后取出 $L_1$ 的两个端点与 $L_2$ 的一个端点，如果是 $L_2$ 被取出的端点与 $L_1$ 相邻，那么问出来一定满足 $L_1$ 的两个端点之间的边不是最短边，否则一定满足 $L_1$ 的两个端点之间的边是最短边（注意到保证了 $|L_1| \leq |L_2|$），然后再考虑更换 $L_2$ 选取的端点或者究竟是与 $L_1$ 哪个端点相邻即可。

询问次数大概是 $O(n \log n)$ 的，实际表现压根不会算，我感觉怎么都不可能常数小于 $1$ 于是就打开了题解看是不是有高明做法，但是发现题解也是类似的随机化，然后我实现了上文的算法，加上对询问记忆化以及特判处理的弧弧长等于 $3$ 的情况（此时只用问一次，弧长更小显然压根不用问）就直接通过了，非常震撼。

由于某些原因写代码的过程比较曲折，所以代码未必能看。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 600;
mt19937 rd(114514);
int n;
vector<int> X,Y;
int r;
map< pair<int,int>,vector< pair<int,int> > > dp[maxn];
void ask(int a,int b,int c){
	vector<int> so;
	so.resize(3);
	so[0]=a,so[1]=b,so[2]=c;
	sort(so.begin(),so.end());
	a=so[0],b=so[1],c=so[2];
	if(dp[a].find(make_pair(b,c))!=dp[a].end()){
		r=0;
		X.clear();
		Y.clear();
		vector< pair<int,int> > res=dp[a][make_pair(b,c)];
		r=res.size();
		X.resize(r),Y.resize(r);
		for(int i=0;i<r;i++){
			X[i]=res[i].first,Y[i]=res[i].second;
		}
		return ;
	}
	cout<<"? "<<a<<" "<<b<<" "<<c<<endl;
	r=0;
	X.clear();
	Y.clear();	
	cin>>r;
	X.resize(r),Y.resize(r);
	vector< pair<int,int> > res;
	for(int i=0;i<r;i++){
		cin>>X[i]>>Y[i];
		res.push_back(make_pair(X[i],Y[i]));
	}
	dp[a][make_pair(b,c)]=res;
}
bool check(int a,int b,int c,int d){
	return max(a,b)==max(c,d)&&min(a,b)==min(c,d); 
}
bool chk(int a,int b,int c){
	ask(a,b,c);
	vector< pair<int,int> > ans;
	ans.resize(r);
	while(r--) ans[r].first=X[r],ans[r].second=Y[r];
	for(pair<int,int> now:ans){
		if(check(now.first,now.second,a,b)==true) return true;
	}
	return false;
}
int cnt=0;
vector<int> solve(vector<int> vec){
	if(vec.size()==3){
		ask(vec[0],vec[1],vec[2]);
		vector<int> res;
		if(Y[0]!=X[1]&&Y[0]!=Y[1]) swap(X[0],Y[0]);
		res.push_back(X[0]);
		res.push_back(Y[0]);
		if(X[1]!=Y[0]) swap(X[1],Y[1]);
		res.push_back(Y[1]);
		return res;
	}
	if(vec.size()<=2) return vec;
	shuffle(vec.begin(),vec.end(),rd);
	int u=vec[0],v=vec[1];
	vector<int> L1,L2;
	L1.push_back(u);
	L2.push_back(v);
	int cut=-1;
	vector<int> res;
	for(int i:vec){
		if(i!=u&&i!=v){
			ask(u,v,i);
			vector< pair<int,int> > ans;
			ans.resize(r);
			while(r--) ans[r].first=X[r],ans[r].second=Y[r];
			for(pair<int,int> now:ans){
				if(check(now.first,now.second,u,v)==true) return res;
			}
			assert(ans.size()<=2);
			if(ans.size()==2) cut=i;
			else{
				if(check(ans[0].first,ans[0].second,u,i)==true) L1.push_back(i);
				else L2.push_back(i);
			}
		}
	}
	vector<int> Vec=vec,l1=L1,l2=L2;
	sort(Vec.begin(),Vec.end());
	sort(l1.begin(),l1.end());
	sort(l2.begin(),l2.end());
	while(1){
		vector<int> res=solve(L1);
		if(res.size()==L1.size()){
			L1=res;
			break;
		}
 	}
	while(1){
		vector<int> res=solve(L2);
		if(res.size()==L2.size()){
			L2=res;
			break;
		}
 	}
	for(int x:L1){
		if(x==cut) assert(0);
	}
	for(int x:L2){
		if(x==cut) assert(0);
	}
	if(cut==-1){
		if(L2.size()<L1.size()) swap(L1,L2);
		ask(L1[0],L1.back(),L2[0]);
		vector< pair<int,int> > ans;
		ans.resize(r);
		while(r--) ans[r].first=X[r],ans[r].second=Y[r];
		bool flag=false;
		for(pair<int,int> now:ans){
			if(check(now.first,now.second,L1[0],L2[0])==true) flag=true;
			if(check(now.first,now.second,L1.back(),L2[0])==true) flag=true;	
		} 
		if(flag==false){
			ask(L1[0],L1.back(),L2.back());
			ans.clear();
			ans.resize(r);
			while(r--) ans[r].first=X[r],ans[r].second=Y[r];
			if(check(ans[0].first,ans[0].second,L1[0],L2.back())==true){
				for(int u:L2) res.push_back(u);
				for(int u:L1) res.push_back(u);
				return res;
			}else{
				reverse(L1.begin(),L1.end());
				for(int u:L2) res.push_back(u);
				for(int u:L1) res.push_back(u);
				return res;
			}
		}else{
			if(check(ans[0].first,ans[0].second,L1[0],L2[0])==true){
				reverse(L2.begin(),L2.end());
				for(int u:L2) res.push_back(u);
				for(int u:L1) res.push_back(u);
				return res;
			}else{
				for(int u:L1) res.push_back(u);
				for(int u:L2) res.push_back(u);
				return res;
			}
		}
	}else{
		if(L1.size()>L2.size()) swap(L1,L2);
		if(L1.size()==1){
			if(L2.size()==1){
				res.push_back(L1[0]);
				res.push_back(cut);
				res.push_back(L2[0]);
				return res;
			}else{
				if(chk(cut,L2[0],L2[1])==true){
					res.push_back(L1[0]);
					res.push_back(cut);
					for(int x:L2) res.push_back(x);
					return res;
				}else{
					reverse(L2.begin(),L2.end());
					res.push_back(L1[0]);
					res.push_back(cut);
					for(int x:L2) res.push_back(x);
					return res;
				}
			}
		}
		if(chk(cut,L1[0],L1[1])==true){
			if(chk(cut,L2[0],L2[1])==true){
				reverse(L2.begin(),L2.end());
				for(int u:L2) res.push_back(u);
				res.push_back(cut);
				for(int u:L1) res.push_back(u);
				return res;
			}else{
				for(int u:L2) res.push_back(u);
				res.push_back(cut);
				for(int u:L1) res.push_back(u);
				return res;
			}
		}else{
			reverse(L1.begin(),L1.end());
			if(chk(cut,L2[0],L2[1])==true){
				reverse(L2.begin(),L2.end());
				for(int u:L2) res.push_back(u);
				res.push_back(cut);
				for(int u:L1) res.push_back(u);
				return res;	
			}else{
				for(int u:L2) res.push_back(u);
				res.push_back(cut);
				for(int u:L1) res.push_back(u);
				return res;
			}
		}
	}
	return res;
}
int p[maxn],x,y;
vector<int> build(){
	for(int i=0;i<n;i++) p[i]=i;
	shuffle(p,p+n,rd);
	x=p[0],y=p[1];
	for(int i=2;i<n;i++){
		if(x==y||x==p[i]||y==p[i]){
			assert(0);
		}
		ask(x,y,p[i]);
		vector< pair<int,int> > ans;
		ans.resize(r);
		while(r--) ans[r].first=X[r],ans[r].second=Y[r];
		if(ans.size()==1&&check(ans[0].first,ans[0].second,x,y)==true) y=p[i];
	}
	vector<int> res;
	vector<int> L1,L2;
	L1.push_back(x);
	L2.push_back(y);
	vector<int> cut;
	for(int i=0;i<n;i++){
		if(i!=x&&i!=y){
			ask(x,y,i);
			vector< pair<int,int> > ans;
			ans.resize(r);
			while(r--) ans[r].first=X[r],ans[r].second=Y[r];
			if(ans.size()==3||(ans.size()==2&&check(ans[0].first,ans[0].second,x,y)!=true&&check(ans[1].first,ans[1].second,x,y)!=true)){
				cut.push_back(i);
			}else if(ans.size()==1){
				if(check(ans[0].first,ans[0].second,x,i)==true) L1.push_back(i);
				else if(check(ans[0].first,ans[0].second,y,i)==true) L2.push_back(i);
				else return res;
			}else return res;
		}
	} 
	while(1){
		vector<int> res=solve(L1);
		if(res.size()==L1.size()){
			L1=res;
			break;
		}
	}
	while(1){
		vector<int> res=solve(L2);
		if(res.size()==L2.size()){
			L2=res;
			break;
		}
	}
	assert(L1.size()==L2.size());
	if(cut.size()==2){
		if(L1.size()==1){
			res.push_back(L1[0]);
			res.push_back(cut[0]);
			res.push_back(L2[0]);
			res.push_back(cut[1]);
			return res;
		}
		if(chk(cut[0],L1[0],L1[1])==true){
			reverse(L1.begin(),L1.end());
			if(chk(cut[0],L2[0],L2[1])==true){
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
				res.push_back(cut[1]);
			}else{
				reverse(L2.begin(),L2.end());
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
				res.push_back(cut[1]);
			}
		}else{
			if(chk(cut[0],L2[0],L2[1])==true){
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
				res.push_back(cut[1]);
			}else{
				reverse(L2.begin(),L2.end());
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
				res.push_back(cut[1]);
			}
		}
		return res;
	}else if(cut.size()==1){
		if(L1.size()==1){
			res.push_back(L1[0]);
			res.push_back(cut[0]);
			res.push_back(L2[0]);
			return res;
		}
		if(chk(cut[0],L1[0],L1[1])==true){
			reverse(L1.begin(),L1.end());
			if(chk(cut[0],L2[0],L2[1])==true){
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
			}else{
				reverse(L2.begin(),L2.end());
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
			}
		}else{
			if(chk(cut[0],L2[0],L2[1])==true){
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
			}else{
				reverse(L2.begin(),L2.end());
				for(int x:L1) res.push_back(x);
				res.push_back(cut[0]);
				for(int x:L2) res.push_back(x);
			}
		}
		return res;
	}else{
		if(L1.size()==1){
			res.push_back(L1[0]);
			res.push_back(L2[0]);
			return res;
		}
		ask(L1[0],L1.back(),L2[0]);
		vector< pair<int,int> > ans;
		ans.resize(r);
		while(r--) ans[r].first=X[r],ans[r].second=Y[r];
		for(pair<int,int> now:ans){
			if(check(now.first,now.second,L2[0],L1[0])==true){
				reverse(L1.begin(),L1.end());
				for(int x:L1) res.push_back(x);
				for(int x:L2) res.push_back(x);
				return res;
			}
			if(check(now.first,now.second,L2[0],L1.back())==true){
				for(int x:L1) res.push_back(x);
				for(int x:L2) res.push_back(x);
				return res;	
			}
		}
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t,k;
	cin>>t>>k;
	for(int i=1;i<=t;i++){
		cin>>n;
		while(1){
			vector<int> res=build();
			if(res.size()==n){
				cout<<"! ";
				for(int i=0;i<n;i++){
					cout<<res[i];
				 	if(i!=n-1) cout<<" ";
				}
				cout<<endl;
				break;
			}
		}
		for(int j=0;j<n;j++) dp[j].clear();
	}
	return 0;
}
```

---

## 作者：shinzanmono (赞：0)

卡常题收收味。

先找到多边形的一条弦 $(u,v)$，如果对于任一点 $x$ 满足 $dis(u,v)\geq \min(dis(u,x),dis(v,x))$，则我们可以判断其是在靠近 $u$ 的方向还是靠近 $v$ 的方向，而 $(u,v)$ 是可以随机选的，算算概率发现选到可行的 $(u,v)$ 的概率在 $\frac{2}{3}$ 左右，可以接受。

现在你有两个未排序的区间，你要将其排序并且合并。合并两个区间是简单的，只需要枚举四种可能的首尾连接方式并且根据距离的大小关系判断即可。而排序我们可以考虑递归使用上面的方法。

对于一个未排序的序列 $A$，接着找一个弦 $(u,v)$，如果对于任一点 $x\in A$ 满足 $dis(u,v)\geq \min(dis(u,x),dis(v,x))$，则我们可以判断其是在靠近 $u$ 的方向还是靠近 $v$ 的方向。而满足这个条件的弦也和上面一样不会太少，直接随就行了。由于这个条件，分出来的两个序列也比较均匀。那显然操作次数就是 $O(n\log n)$ 的。这样，我们就获得了一个可以拿很高的分数的做法。

考虑卡次数的常。

1. 对三个点的序列问一次就能出来。三个点，肯定有至少两个点对是相邻的，问一次这两个点对就都知道了，直接拼凑即可。
2. 合并序列时，如果前三种情况均不满足就直接返回第四种。
3. 考虑每次随机的时候先随机三个点，然后排除最小的一条边。这样显然要比之前的直接随机两个点的做法不劣，而这一次询问的必定会在后面再问一次，记忆化就不会导致额外的询问。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<random>
#include<map>
std::mt19937 rnd(0xb6e0);
std::map<std::vector<int>,std::vector<std::pair<int,int>>>res;
std::pair<int,int>pair(int a,int b){
  if(a>b)std::swap(a,b);
  return std::make_pair(a,b);
}
std::vector<std::pair<int,int>>Query(int a,int b,int c){
  std::vector<int>V({a,b,c});
  std::sort(V.begin(),V.end());
  if(res.find(V)!=res.end())return res[V];
  a=V[0],b=V[1],c=V[2];
  std::cout<<"? "<<a<<" "<<b<<" "<<c<<std::endl;
  int r;
  std::cin>>r;
  std::vector<std::pair<int,int>>ans;
  for(int i=1,a,b;i<=r;i++)std::cin>>a>>b,ans.push_back(pair(a,b));
  return res[V]=ans;
}
int query(int a,int b,int c){
  auto res=Query(a,b,c);
  int ans=0;
  for(auto p:res){
    if(pair(a,b)==p)ans|=1;
    if(pair(b,c)==p)ans|=2;
    if(pair(a,c)==p)ans|=4;
  }
  return ans;
}
bool split(std::vector<int>vec,int a,int b,std::vector<int>&l,std::vector<int>&r){
  l.clear(),r.clear();
  for(int x:vec){
    if(x==a)l.push_back(x);
    else if(x==b)r.push_back(x);
    else{
      int res=query(a,b,x);
      if(res&2)r.push_back(x);
      else if(res&4)l.push_back(x);
      else return false;
    }
  }
  return true;
}
std::vector<int>operator+(std::vector<int>a,std::vector<int>b){
  std::vector<int>res(a);
  return res.insert(res.end(),b.begin(),b.end()),res;
}
std::vector<int>reverse(std::vector<int>a){
  return std::reverse(a.begin(),a.end()),a;
}
std::vector<int>merge(std::vector<int>A,std::vector<int>B){
  if(A.size()>B.size())std::swap(A,B);
  if(A.empty()||B.size()<=1)return A+B;
  if(A.size()==1)return query(A[0],B[0],B[1])&1?A+B:B+A;
  int res=query(B[0],A[0],A[1]);
  if(res!=2){
    if(res&4)return A+B;
    else return reverse(A)+B;
  }
  res=query(A[1],A[0],B.back());
  if(res!=1){
    if(res&4)return A+reverse(B);
    else return reverse(A)+reverse(B);
  }
  res=query(A[A.size()-2],A.back(),B[0]);
  if(res!=1){
    if(res&2)return A+B;
    else return reverse(A)+B;
  }
  return A+reverse(B);
}
std::vector<int>solve(std::vector<int>vec){
  if(vec.size()<=2)return vec;
  if(vec.size()==3){
    int res=query(vec[0],vec[1],vec[2]);
    if(res&1&&res&2)return vec;
    if(res&1&&res&4)return std::vector<int>({vec[2],vec[0],vec[1]});
    if(res&2&&res&4)return std::vector<int>({vec[1],vec[2],vec[0]});
  }
  std::vector<int>l,r;
  while(true){
    int N=vec.size(),a=rnd()%N,b=rnd()%N,c=rnd()%N;
    while(a==b||b==c||c==a)a=rnd()%N,b=rnd()%N,c=rnd()%N;
    a=vec[a],b=vec[b],c=vec[c];
    int res=query(a,b,c);
    if(res&1){
      if(res&2==0)a=b;
      else b=c;
    }
    if(split(vec,a,b,l,r))return merge(solve(l),solve(r));
  }
}
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t,k,n;
  std::cin>>t>>k;
  while(t--){
    res.clear();
    std::cin>>n;
    std::vector<int>vec;
    for(int i=0;i<n;i++)vec.push_back(i);
    auto res=solve(vec);
    std::cout<<"! ";
    for(int x:res)std::cout<<x<<" ";
    std::cout<<std::endl;
  }
  return 0;
}
```

---

