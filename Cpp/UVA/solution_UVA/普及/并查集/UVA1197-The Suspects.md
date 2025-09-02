# The Suspects

## 题目描述

在一所大学里有 $n$ 个学生（这些学生的编号为 $0\sim  n-1$）。这些学生由于兴趣爱好等原因组成了 $m$ 个群体。

由于非典（$\mathrm{SARS}$）流行，该大学的学生会需要排除可能的非典患者。

由于非典传染性强，学生会的成员假定：如果一个群体中有一个人是非典患者，那么这个群体中的所有人都是非典患者。

现在已知编号为 $0$ 的学生为非典患者。请你找出这些学生中非典患者的人数。

# 题解

## 作者：misaka_八重樱 (赞：5)

这题是一个纯并查集题

从“如果一个群体中有一个人是非典患者，那么这个群体中的所有人都是非典患者。”这句话可以简化成有多个集合，求与0在同一个集合里的所有人数

先给个find函数路径压缩
```cpp
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
```
对并查集不熟的小伙伴可以百度一下，这里推荐一个，本人认为讲的很不错

[并查集](https://www.cnblogs.com/xzxl/p/7226557.html)

一个群体中的合并操作
```cpp
if(find(x)!=find(y)) f[f[x]]=f[y];//如果x与y不在同一集合中，将祖先和祖先合并即可使两集合合并
```
直接上代码


```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int f[30050];
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);//路径压缩
}
int main()
{
	while(1)
	{	
		int n,m;
		cin>>n>>m;
		if(n==0&&m==0) break;
		for(int i=0;i<n;i++)
			f[i]=i;				//先全部初始化为自己，即为自己就是一个集合
		for(int i=1;i<=m;i++)
		{
			int num;cin>>num;	//人数
			int x;cin>>x;		//先输第一个数，方便合并
			for(int j=2;j<=num;j++)
			{
				int y;cin>>y;
				if(find(x)!=find(y)) f[f[x]]=f[y];//第一个和后面输入的挨个合并
			}
		}
		int ans=0;
		for(int i=0;i<n;i++)
			if(find(0)==find(i)) ans++;	//如果查找0的祖先是某个编号的祖先时，说明这个人会被0感染，计数器+1
		cout<<ans<<endl;	//输出会被感染的人数
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：4)

    沙发题解  
这道题是很裸的一道并查集题，只不过合并时要带权值合并，查找时带上路径压缩即可。  
找祖宗 ~~秀一波极限缩行~~  ：  

```cpp
int find(int u){return f[u]==u?u:f[u]=find(f[u]);}
```  
合并：  
```cpp
void merge(int a,int b){ //把b合并到a,带权值
    a=find(a);b=find(b);
    if(a!=b){
        s[a]+=s[b];
        f[b]=a;
    }
}
``` 
话不多说，上代码：  
```cpp
#include<iostream>
using namespace std;
int f[30001],s[30001];//f:并查集,s:size,即儿子数
int n,m;

void ChuShiHua(int n){ //初始化
    for(int i=0;i<n;i++)
        f[i]=i,s[i]=1;
}

int find(int u){return f[u]==u?u:f[u]=find(f[u]);} //寻找祖先(带路径压缩)

void merge(int a,int b){ //把b合并到a,带权值
    a=find(a);b=find(b);
    if(a!=b){
        s[a]+=s[b];
        f[b]=a;
    }
}

int main(){
    ios::sync_with_stdio(false);
    while(true){
        cin>>n>>m;
        if(m==0&&n==0) return 0;
        ChuShiHua(n);
        for(int i=1;i<=m;i++){
            int k,one,two;
            cin>>k>>one;
            for(int j=1;j<k;j++){
                cin>>two;
                merge(one,two); //合并
            }
        }
        cout<<s[find(0)]<<endl; //0号的祖先的儿子数即为患者
    }
    return ~~(0-0);  //结尾卖萌
}
```

---

## 作者：hswfwkj_ (赞：3)

其实就是一道特别水的并查集题目。

如果不会并查集请挪步此处：

[并查集板子题](https://www.luogu.com.cn/problem/P3367)

那么知道了并查集之后呢，我们的步骤就只分如下三个步骤：

1. 输入

1. 合并

1. 判断

### 输入
这部分没有必要细讲，直接跳过。
### 合并
对于每一个群体的输入，我们可以先输入这个群体的第一个人，然后一个一个输入剩下的人，再把剩下的人都合并到第一个人就行了。
### 判断
众所周知，并查集判断两个数是否在同一个集合里，只需要一行代码：

`if(find(x)==find(y))`

而在这里，我们只需一个循环从 $1$ 到 $n-1$ 扫一遍，判断它们是不是与 $0$ 在同一个集合就行了。

那么直接贴上代码，应该比较通俗易懂吧：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[40000];
int find(int k){//路径压缩函数
	return a[k]==k?k:(a[k]=find(a[k]));
}
int main(){
    int n,m;
	while(cin>>n>>m){
		memset(a,0,sizeof(a));//每次都要重新初始化数组
		int i,j,x,y,num,ans=1;//因为一开始就有一个学生有疫病，所以 ans 初始化为1
		if(!n&&!m)break;
		for(i=0;i<n;i++)a[i]=i;//记住是从 0 到 n-1！
		for(i=1;i<=m;i++){
			cin>>num>>x;//先读入群体里人的个数和第一个人的编号，这样方便之后合并
			for(j=2;j<=num;j++){
				cin>>y;
				a[find(y)]=find(x);
			}
		}
		for(i=1;i<n;i++)
			if(find(i)==find(0))//判断是否在同一集合
				ans++;
		cout<<ans<<endl;
	}
	return 0;
}
```
谢谢大家！

---

## 作者：NuoCarter (赞：2)


## 众所周知：

并查集可以用来维护图的连通关系

那么

## 我们为什么不可以直接建图跑连通块呢？

。

### 思维难度小


### 代码细节少


### 常数也小

直接放代码了

细节：

1：此题存的是无向边
所以边数组要开两倍大小

2：多组数据记得memset和清空变量


```cpp
#include<bits/stdc++.h>
using namespace std;
int Next[60005];
int to[60005];
int head[30005];
int tot;
int n,m;
bool v[30005];
int ans;
inline void add(int x,int y){
	to[++tot]=y;
	Next[tot]=head[x];
	head[x]=tot;
	return;
}
inline void dfs(int x){
	ans++;
	v[x]=true;
	for(register int i=head[x];i!=-1;i=Next[i]){
		int y=to[i];
		if(!v[y]){dfs(y);}
	}
}
int main(){
	while(~scanf("%d%d",&n,&m)){
		if(n==0&&m==0){
			return 0;
		}
		memset(Next,-1,sizeof(Next));
		memset(head,-1,sizeof(head));
		memset(to,0,sizeof(to));
		memset(v,false,sizeof(v));
		int man=0;
		ans=0;
		int st;
		int u;
		for(register int i=1;i<=m;++i){
			scanf("%d",&man);
			scanf("%d",&st);
			for(int i=2;i<=man;++i){
				scanf("%d",&u);
				add(st,u);
				add(u,st);
				st=u;
			}
		}
		dfs(0);
		printf("%d\n",ans);	
	}
	return 0;
}
```




---

## 作者：SUPERXWX (赞：1)

该题显然是一道**并查集**，题目简单来说就是 : 求多少人和 $0$ 号学生在一个子集里。

因为 **$0$ 是已知的患者**，而且上述的操作并没有算到 $0$ 号学生，所以我们需要在答案上加一。

并查集本蒟蒻怕讲不明白，所以只能献上洛谷板子的链接:[在这里！](https://www.luogu.com.cn/problem/P3367)

下面奉上代码：

```cpp
#include <bits/stdc++.h>//万能头，几乎包含了所有头文件，但不包括<windows.h> 
using namespace std;
int m,n,a[30050]={0},people,s=0,fa[30050]={0}; 
int find(int l){
	if(fa[l]==l){
		return l;
	}
	else{
		return find(fa[l]);
	}
}//寻找该变量的祖宗。 
void hb(int x,int y){
	fa[find(x)]=find(y);
}//将两个量合（h）并（b）至一个子集(路径压缩)。
//路径压缩后，树的层数变少了，寻找祖宗的速度就会变快。 
//上面两个函数是学并查集必须要学会的函数，这么一顿操作过后查询祖宗就比暴力搜快了不止一点 
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);这是怕模拟赛时忘了打freopen,下面的fclose也是如此。 
	while(1){
		s=0;
		memset(fa,0,sizeof(fa));//务必清零！ 
		cin>>n>>m;//判断输入。 
		if(m==0&n==0){
			break;
		}
		else{
			for(int i=0;i<n;i++){
				fa[i]=i;
			}//重置祖宗。 
			for(int i=1;i<=m;i++){
				memset(a,0,sizeof(a));//每次操作前务必清零！ 
				cin>>people>>a[1];//先把第一个人输入好合并。 
				for(int j=2;j<=people;j++){
					cin>>a[j];//如果此时再输入第一个人就会重复。 
					hb(a[1],a[j]);//只需要将其与第一个人合并，就可以同步祖宗。 
				}
			}
			for(int i=1;i<n;i++){
				if(find(i)==find(0))//并查集判断，这是必须要学会的。 
				s++;
			}
			cout<<s+1<<endl;//加上0号患者。 
		}
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
//完结撒花！ 
```


---

## 作者：45dino (赞：1)

一道并查集模板题。


如果这一组里有0，这一组就全被感染了。

如果这一组是a，b，c，根据并查集的性质，只要合并ab，bc就可以了（不需要合并ac）。

唯一的问题是，0必须放在根部，才能判断是不是和0在同一组（见下图）

![](https://cdn.luogu.com.cn/upload/image_hosting/ayq87s0a.png)

如果这样，在左边并查集中，就会显示不和0在一组，即find(x)!=0。

可以制定一个规则，使并查集的节点上小下大，于是变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/qehyjmlx.png)

这样，所以和0在同一个集里的find值都等于0，问题便迎刃而解了。

最后要注意多解的处理。

喜闻乐见的代码：

```
#include<bits/stdc++.h>
using namespace std;
int fa[300001],n,m; 
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		fa[i]=i;
	while(n!=0||m!=0)
	{
		int ans=0;
		while(m--)
		{
			int num;
			cin>>num;
			int a,b;
			cin>>a;
			for(int i=1;i<num;i++)
			{
				cin>>b;
				fa[max(find(a),find(b))]=min(find(a),find(b));
				a=b;
			}
		}
		for(int i=0;i<n;i++)
			if(find(i)==0)
				ans++;
		cout<<ans<<endl;
		cin>>n>>m;
		for(int i=0;i<n;i++)
			fa[i]=i;
	} 
	return 0;
}
```

后记：如果写成find（i）==find（0）就不需要按上小下大的顺序排列，请读者自行尝试。

---

## 作者：Water_Cows (赞：0)

- $\texttt{UVA1197}$ The Suspects 

- 算法：并查集（~~俗称冰茶姬~~，不会并查集的看[这里](https://www.luogu.com.cn/blog/yufan/suan-fa-zhi-bing-zha-ji)，十分详细哦，看不懂给我留言就行了）

- 题目大意：求与 $0$ 连通的节点数量

- 思路

  - 直接并查集维护即可
  - 不要带权并查集哦，（~~我绝对不会告诉你我开始想的就是带权并查集~~）。。。
  - 最后所有节点搜一遍是否与 $0$ 连通即可。

- 易错点：无

- Code

  ```cpp
  #include <iostream>
  using namespace std;
  
  const int N = 30000 + 7;
  
  int n, m, ans;
  
  struct parent
  {
      int fa[N];
  
      void mem(int n)
      {
          for(int i=0; i<n; i++)
              fa[i] = i;
      }
  
      int find(int x)
      {
          if(fa[x] == x) return x;
          return fa[x] = find(fa[x]); 
      }
  
      void uni(int x, int y)
      {
          int tx = find(x);
          int ty = find(y);
  
          if(tx != ty)
              fa[tx] = ty;
      }
  
      void write(int n)
      {
          int ans = 1;
          for(int i=1; i<n; i++)
              if(find(i) == find(0))
                  ans++;
          cout << ans << endl;
      }
  }e;
  
  inline void init(int n)
  {
      e.mem(n);
      ans = 1;
  }
  
  inline void Solve()
  {
      init(n);
      for(int i=1; i<=m; i++)
      {
          int now, x1, x2;
          cin >> now;
          cin >> x1;
          for(int j=2; j<=now; j++)
          {
              cin >> x2;
              e.uni(x1, x2);
              x2 = x1;
          }
      }
      e.write(n);
  }
  
  int main()
  {
      //freopen("input", "r", stdin);
  
      ios::sync_with_stdio(false);
      cin.tie(0); cout.tie(0);
  
      while(cin >> n >> m)
      {
          if(n == 0 && m == 0) break;
          Solve();
      }
  }
  ```

  



---

