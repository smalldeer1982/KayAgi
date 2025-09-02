# Noise Level

## 题目描述

The Berland's capital has the form of a rectangle with sizes $ n×m $ quarters. All quarters are divided into three types:

- regular (labeled with the character '.') — such quarters do not produce the noise but are not obstacles to the propagation of the noise;
- sources of noise (labeled with an uppercase Latin letter from 'A' to 'Z') — such quarters are noise sources and are not obstacles to the propagation of the noise;
- heavily built-up (labeled with the character '\*') — such quarters are soundproofed, the noise does not penetrate into them and they themselves are obstacles to the propagation of noise.

A quarter labeled with letter 'A' produces $ q $ units of noise. A quarter labeled with letter 'B' produces $ 2·q $ units of noise. And so on, up to a quarter labeled with letter 'Z', which produces $ 26·q $ units of noise. There can be any number of quarters labeled with each letter in the city.

When propagating from the source of the noise, the noise level is halved when moving from one quarter to a quarter that shares a side with it (when an odd number is to be halved, it's rounded down). The noise spreads along the chain. For example, if some quarter is located at a distance $ 2 $ from the noise source, then the value of noise which will reach the quarter is divided by $ 4 $ . So the noise level that comes from the source to the quarter is determined solely by the length of the shortest path between them. Heavily built-up quarters are obstacles, the noise does not penetrate into them.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF847I/0a8ce4c074a103c21f7e8facf314824c3efeff45.png)The values in the cells of the table on the right show the total noise level in the respective quarters for $ q=100 $ , the first term in each sum is the noise from the quarter 'A', the second — the noise from the quarter 'B'.The noise level in quarter is defined as the sum of the noise from all sources. To assess the quality of life of the population of the capital of Berland, it is required to find the number of quarters whose noise level exceeds the allowed level $ p $ .

## 说明/提示

The illustration to the first example is in the main part of the statement.

## 样例 #1

### 输入

```
3 3 100 140
...
A*.
.B.
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3 2 8
B*.
BB*
BBB
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 4 5 4
..*B
..**
D...
```

### 输出

```
7
```

# 题解

## 作者：xzggzh1 (赞：2)

题意：


给一个 $n\times m$ 的方格和 $q,p$ 的值。

其中 `.` 表示不产生噪音但可以传播的格子。`*` 表示不产生噪音也不会传播噪音的格子。`A~Z` 表示产生噪音的方格 ，产生 $(X-'A'+1)*q$ 的噪音（`A` 表示 $q$，`B` 表示 $2*q$ … `Z`表示 $26*q$）。

噪音可以向四个方向传播，每经过一个格子就会减半（向下取整），同一个噪声源对于一个格子产生的传播不叠加。

问最后有多少格子的噪声的值大于 $p$。

---

简单模拟题，直接对于每个点 $\rm bfs$ 即可。注意，影响的距离要用的最短。


---

代码有点冗长但是十分的基础：

```cpp
char c[250][250];
int noise[250][250],n,m,p,q;
int use[250][250],d1[4]={0,0,1,-1},d2[4]={1,-1,0,0}; 
vector<pair<int,int> > vvis;
int dist[255][255];
void bfs(int a,int b,int energy){
	vvis.clear();queue<pair<int,int> > Q;
	Q.push(mp(a,b));dist[a][b]=energy;
	while (!Q.empty()){
		pair<int,int> x=Q.front();Q.pop();
		if (dist[x.first][x.second]<=1) continue;
		for (int i=0;i<4;i++){
			int X=x.first+d1[i],Y=x.second+d2[i];
			if (X>=0 && Y>=0 && X<n && Y<m && dist[X][Y]==0 && c[X][Y]!='*'){
				dist[X][Y]=dist[x.first][x.second]/2;
				Q.push(mp(X,Y));
				vvis.pb(mp(X,Y));
			}
		}
	}
	vvis.pb(mp(a,b));
	for (int i=0;i<vvis.size();i++){
		noise[vvis[i].first][vvis[i].second]+=dist[vvis[i].first][vvis[i].second];
		dist[vvis[i].first][vvis[i].second]=0;
	}
}
int main()
{
	cin>>n>>m>>p>>q;
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	cin>>c[i][j];		
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	if(c[i][j]<='Z'&&c[i][j]>='A')
	bfs(i,j,(c[i][j]-'A'+1)*p);			
	int ans=0;	
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	if(noise[i][j]>q)ans++;
	cout<<ans<<endl;
} 
```

---

