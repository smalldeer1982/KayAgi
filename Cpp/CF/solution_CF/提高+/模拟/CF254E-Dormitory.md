# Dormitory

## 题目描述

Student Vasya came to study in Berland State University from the country, so he is living in a dormitory. A semester has $ n $ days, and in each of those days his parents send him some food. In the morning of the $ i $ -th day he receives $ a_{i} $ kilograms of food that can be eaten on that day and on the next one (then the food goes bad and becomes unfit for consumption).

Every day Vasya eats $ v $ kilograms of food. It is known that Vasya's parents do not allow him to starve, so there always is enough food for Vasya. Vasya has $ m $ friends who sometimes live with him. Let's index the friends from 1 to $ m $ . Friend number $ j $ lives with Vasya from day $ l_{j} $ to day $ r_{j} $ , inclusive. Also, the $ j $ -th friend requires $ f_{j} $ kilograms of food per day. Usually Vasya's friends eat in the canteen, but sometimes generous Vasya feeds some of them. Every day Vasya can feed some friends who live with him this day (or may feed nobody).

Every time Vasya feeds his friend, he gives him as much food as the friend needs for the day, and Vasya's popularity rating at the University increases by one. Vasya cannot feed the same friend multiple times in one day. In addition, he knows that eating habits must be regular, so he always eats $ v $ kilograms of food per day.

Vasya wants so choose whom he will feed each day of the semester to make his rating as high as possible. Originally Vasya's rating is 0 because he is a freshman.

## 样例 #1

### 输入

```
4 1
3 2 5 4
3
1 3 2
1 4 1
3 4 2
```

### 输出

```
7
1 2
1 2
3 2 1 3
2 2 3
```

# 题解

## 作者：RedLycoris (赞：1)

题目大意：

有 $n$ 天，第 $i$ 天你会收到 $a_i$ 份食物。食物有保质期，第 $i$ 天收到的食物只能在第 $i$ 天和第 $i+1$ 天食用。

你还有 $m$ 个朋友。第 $i$ 个朋友会在第 $l_i$ 至 $r_i$ 天拜访你，食量是 $c_i$ 份食物。

你每天可以选择一些朋友供应食物（必须供给正好 $c_i$ 份食物，一个朋友一天只能供给一次），每贡献一人次你的人气值就会 $+1$。

同时，你每天必须吃 $v$ 份食物。

问你 $n$ 天后你的人气值最大是多少。

题解：

令 $dp_{i,j}$ 表示考虑到第 $i$ 天，昨天剩下了 $j$ 份食物时你最大的人气值。

转移：

很显然，我们每一天肯定会先吃昨天的剩饭，不够了再吃今天的饭。

然后选择朋友的话，我们可以贪心的选：按照朋友的饭量从小到大排序，选最小的前 $k$ 个。

具体可以参考代码

Code:
```cpp
const int mxn=444;
int n,v,m;
int a[mxn];
vector<pair<int,int> >c[mxn];
int dp[mxn][mxn*2],pre[mxn][mxn*2],preg[mxn][mxn*2]; //pre[][]记录剩饭由哪儿转移过来，preg记录了当天请了饭量前多少小的朋友吃饭
inline void solve(){
	cin>>n>>v;
	for(int i=1;i<=n;++i)cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;++i){
		int l,r,t;cin>>l>>r>>t;
		for(int j=l;j<=r;++j)c[j].push_back(mp(t,i));
	}
	for(int i=1;i<=n;++i)sort(c[i].begin(),c[i].end());
	for(int i=0;i<mxn;++i)for(int j=0;j<mxn*2;++j)dp[i][j]=-1145141;
	dp[1][0]=0;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=800;++j){//dp[i][j]表示考虑到第i天，昨天剩下了j的食物所能得到的最大值 
			if(dp[i][j]<0)continue;
			int yes=j,tod=a[i];    //分别代表昨天的剩饭和今天新增的饭
			if(yes>=v)yes-=v;
			else tod-=(v-yes),yes=0;  //先处理今天自己吃的饭
			int x=tod+yes;
			if(dp[i][j]>dp[i+1][tod]){
				dp[i+1][tod]=dp[i][j];
				pre[i+1][tod]=j;
				preg[i+1][tod]=0;
			}
			int sum=0;
			for(int k=0;k<c[i].size();++k){
				sum+=c[i][k].first;
				if(sum>x)break;
				int rem=min(tod,x-sum);  //还是先吃剩饭，然后处理昨天不能保留到明天的饭
				if(dp[i][j]+k+1>dp[i+1][rem]){
					dp[i+1][rem]=dp[i][j]+k+1;
					pre[i+1][rem]=j;
					preg[i+1][rem]=k+1;
				}
			}
		}
	}
	int pos=0;
	for(int i=1;i<=800;++i)if(dp[n+1][i]>dp[n+1][pos])pos=i;
	cout<<dp[n+1][pos]<<'\n';
	vector<int>bk;
	bk.clear();
	int lst=pos;
	for(int i=n+1;i>1;--i){
		bk.push_back(preg[i][lst]);
		lst=pre[i][lst];
	}
	for(int i=bk.size()-1;~i;--i){
		cout<<bk[i]<<' ';
		for(int j=0;j<bk[i];++j)cout<<c[bk.size()-i][j].second<<' ';
		cout<<'\n';
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout); 
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	//cin>>T;
	for(;T--;)solve();
	return 0;
}
```

---

