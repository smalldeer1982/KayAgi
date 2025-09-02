# [ARC036D] 偶数メートル

## 题目描述

高桥君所在的国家有 $N$ 座城市，编号为 $1$ 到 $N$。初始时没有道路，于是国家准备修建几条连接不同城市的双向道路。

由于高桥君很喜欢偶数，所以在从一座城市到达另外一座城市时，即使绕远路，或者走同一条路多次，也要使得走的总距离为偶数。但是在走过一条路后，高桥君不会马上再走一遍这条路。

高桥君有时会指定两座不同的城市，问他是否能用上述方式从其中一座走到另外一座。

由于国家还在建设道路，因此在不同时间提出的相同问题可能有不同的答案。

## 样例 #1

### 输入

```
5 9
1 1 2 3
1 1 3 2
1 3 5 5
2 1 5 1
2 2 5 1
1 2 4 4
1 1 4 6
2 1 5 1
2 3 5 1```

### 输出

```
NO
YES
YES
YES```

## 样例 #2

### 输入

```
5 7
1 1 2 3
1 2 4 4
1 5 3 1
2 1 3 1
2 5 3 1
1 3 1 2
2 3 4 1```

### 输出

```
NO
NO
NO```

## 样例 #3

### 输入

```
3 6
1 1 2 1
1 1 3 3
1 2 3 2
1 2 1 2
2 1 3 1
2 2 3 1```

### 输出

```
YES
YES```

# 题解

## 作者：zxh_qwq (赞：1)

### AT_arc036_d 题解

看到奇偶性，再看到合并，一眼分奇偶点的并查集。

令 $c_u$ 为奇点，$c_{u+n}$ 为偶点，每次直接合并就行了。

当边 $u,v$ 的权值为奇数时，为了不让奇偶性改变，将 $c_u$ 与 $c_{v+n}$ 合并，将 $c_{u+n}$ 与 $c_v$ 合并。

当边 $u,v$ 的权值为偶数时，为了不让奇偶性改变，将 $c_u$ 与 $c_v$ 合并，将 $c_{u+n}$ 与 $c_{v+n}$ 合并。

所以我们可以写出一份短小不压行的代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int fa[200010];
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]); 
}
void merge(int x,int y){
	fa[find(x)]=find(y);
}
main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n*2;i++)fa[i]=i;
	int w,x,y,z;
	while(m--){
		cin>>w>>x>>y>>z;
		if(w==1){
			if(z%2==0){
				merge(x,y);
				merge(x+n,y+n);
			}
			else{
				merge(x,y+n);
				merge(x+n,y);
			}
		}
		else{
			if(find(x)==find(y))cout<<"YES"<<endl;
			else cout<<"NO"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

### 思路

考虑并查集，具体来说，将一个点拆成奇点和偶点，设每次连边为 $(u,v,w)$，分讨。

1. $w$ 为偶数，因为奇偶性不会改变，因此将 $u$ 的奇点和 $v$ 的奇点合并，将 $u$ 的偶点和 $v$ 的偶点合并。

2. $w$ 为奇数，因为奇偶性改变，因此将 $u$ 的奇点和 $v$ 的偶点合并，将 $u$ 的偶点和 $v$ 的奇点合并。

询问直接判断 $u$ 和 $v$ 的偶点是否联通即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,m,fa[200010];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
signed main(){
	n=read();m=read();iota(fa+1,fa+1+(n<<1),1);
	while(m--){
		int opt=read(),u=read(),v=read(),w=read();
		if(!(opt^1)){
			if(w&1^1){merge(u,v);merge(u+n,v+n);}
			else{merge(u,v+n);merge(u+n,v);}
		}else cout<<(find(u)^find(v)?"NO\n":"YES\n");
	}
	return 0;
}
```

---

## 作者：star_field (赞：0)

### 解题思路
看到两座城市是否联通且只与边权奇偶相关，考虑并查集。但是高桥只能走偶数的路程，所以需要一点技巧。

对于样例 1，我们可以构造一个这样的图（最终情况）：
![](https://cdn.luogu.com.cn/upload/image_hosting/bpdtagn8.png)

例如，对 $1\to2$，我们可以转化为 $1\to4\to2$。

那这样我们可以另外造一个图，根据边权的奇偶让它与原有的图相连，同时自己内部也相连（在下面给出解释）：
![](https://cdn.luogu.com.cn/upload/image_hosting/a1cwora0.png)
这里把原来奇边权的边拆开了，只留下偶边权的，$d+n$ 代表共有 $n$ 个节点的情况下节点 $d$ 的对应点。这里原节点与对应节点的边是奇边权的，对应节点与对应节点间是偶边权的。如果节点与节点间不能通过偶权边直达（如 $3\to5$）那么我们就考虑走对应节点。因为原节点与对应节点的边是奇边权，所以只要它们联通，就应该走了两次奇权边，变成了偶数。
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,Q,f[200001],w,x,y,z; //开两倍数组（因为还有对应节点）
int find(int x){ //并查集
	if (f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void add(int x, int y){ //建边
	x=find(x);
	y=find(y);
	f[x]=y;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>N>>Q;
	for(int i=1;i<=2*N;i++) f[i]=i; //并查集初始化
	for(int i=1;i<=Q;i++){
		cin>>w>>x>>y>>z;
		if(w==1){
			if(z%2==1){ //奇权边
				add(x,y+N); //原节点与对应节点建边
				add(x+N,y);
			}
			else{ //偶权边
				add(x,y); //原节点与原节点建边
				add(x+N,y+N); //对应节点与对应节点建边
			}
		}
		else{
			if(find(x)==find(y)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

