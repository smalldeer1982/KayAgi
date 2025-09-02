# New Year Cards

## 题目描述

亚历山大开始回复朋友们写的新年问候。亚历山大有 $n$ 个朋友，每个朋友都给亚历山大写了一张新年贺卡。我们按朋友给亚历山大发信的先后顺序来将朋友从 $1$ 到 $n$ 编号。我们以同样的方式来对这些卡片进行编号，例如第 $2$ 个朋友的卡片的编号为 $2$ 。

亚历山大也寄贺卡，但他喜欢使用以前朋友发给他的卡片（一开始，亚历山大没有贺卡）。他寄贺卡遵守两条原则：

$1.$ 他不会把该朋友邮寄给他的贺卡再寄回去。

$2.$对于当前他所拥有的贺卡，他只会选择他最喜欢的卡给朋友。

亚历山大计划给每一个朋友发送一张卡片（同一张牌可以多次利用）。

亚历山大以及他的朋友都有偏好列表（即喜欢的卡牌列表），表格从 $1$ 到 $n$ 。数字越小，这张卡越受喜欢。

你的任务是找到寄卡片的时间表，以确定亚历山大寄贺卡的时间，以取悦他的朋友（则他的朋友尽可能多的收到自己喜欢的贺卡）。

需要注意的是，亚历山大不会自由选择发送哪张卡，但他始终严格遵守这两条规则。

## 样例 #1

### 输入

```
4
1 2 3 4
4 1 3 2
4 3 1 2
3 4 2 1
3 1 2 4
```

### 输出

```
2 1 1 4
```

# 题解

## 作者：Allanljx (赞：2)

## 思路
对于第 $i$ 个人，按顺序枚举每张贺卡，当当前贺卡就是 $i$ 时跳过。然后枚举在当前贺卡得到前的每张贺卡，确保它们的喜爱程度要小于当前贺卡的喜爱程度或这张卡片就是 $i$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[305][305];
int b[305];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)//喜爱程度（数越小说明越喜爱）
	{
		int x;
		cin>>x;
		b[x]=i;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==i) continue;//不能自己个自己贺卡
			int f=0;
			for(int k=1;k<a[i][j];k++)
			{
				if(b[k]<b[a[i][j]]&&k!=i) f=1;//发不出去
			}
			if(f) continue;
			cout<<a[i][j]<<' ';
			break;
		}
	}
}
```


---

## 作者：Eazin_star (赞：1)

### 思路
这道题就直接枚举，把喜爱值存起来，然后直接一个一个朋友枚举。如果这张贺卡是这个朋友给你的，直接跳过。枚举卡片，若是最优则输出，否则继续枚举。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[505], val[505][505];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) 
			scanf("%d", &val[i][j]);
	}		
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		a[x] = i;	
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (val[i][j] == i) continue; //如果这张贺卡是这个朋友送的，直接跳过
			bool f = 1;
			for (int k = 1; k < val[i][j]; k++) { //遍历贺卡
				if (a[k] < a[val[i][j]] && k != i) f = 0;	
			}
			if (!f) continue; //如果不是最优，继续枚举
			printf("%d ", val[i][j]); //是的话，输出
			break; //中断
		}
	}	
	return 0;
}
```




---

## 作者：ys_kylin__ (赞：1)

这道题是一道枚举，不用任何技术含量，$O(n^3)$ 解决。首先输入，这里需要记下亚历山大本人对每张卡的喜爱程度，记作 mp。

然后从一枚举每一个朋友，再从一枚举每张贺卡（如果这张贺卡是朋友给你的，跳过），最后从一到该卡枚举，确认是最优，最优就输出，并切换到下一个人，否则继续枚。这里注意，假设枚举到朋友给你的卡，不用比较。

其实有很多可以优化的，但没必要，~~绝对不是因为我懒~~。

代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505][505];
int mp[505];
int main() {
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(int i=1,x;i<=n;i++) {
		scanf("%d",&x);
		mp[x]=i;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			if(a[i][j]==i) continue;//不能发对面给你的
			int fl=0;
			for(int k=1;k<a[i][j];k++)
            	if(mp[k]<mp[a[i][j]] && k!=i) {fl=1;break;}//假如他不是最优，直接跳过
			if(fl==1) continue;
			printf("%d ",a[i][j]);
			break;
		}
	return 0;
}
```

---

## 作者：nj_peak (赞：0)

# 一道简单的枚举题！！！

其实 $O(n^3)$ 就可以过。

## 思路
使用一个 $a$ 数组来记录喜好程度，在一一枚举所有朋友和枚举贺卡。

当然，如果是朋友送的贺卡，就要跳过啦！

如果是最优，就输出，不然就跳过。
## 代码：
```cpp
#include<bits/stdc++.h>
#define endl "\n"
#define LL long long 
using namespace std;
const int MAXN=1145;
const int MAXX=114514;
LL n,f[MAXN][MAXN],a[MAXX],ans;
void scanfin(){ 				//输入 
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>f[i][j];
		}
	}
}
void Likeness_level(){			//喜好程度 
	for(int i=1;i<=n;i++){
		scanf("%lld",&ans);
		a[ans]=i;
	}
}
void send_cards(){				//查找所有朋友和卡片 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(f[i][j]==i) continue;
			int res=0;
			for(int k=1;k<=f[i][j];k++){
				if(a[k]<a[f[i][j]] && k!=i)	{
					res=1;
					break;	
				}
			}
			if(res==1) continue;
			printf("%lld ",f[i][j]);
			break;
		}
	}
	return ;
}
int main(){
	scanfin();
	Likeness_level();
	send_cards();
	return 0;

}
```


---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF140B](https://www.luogu.com.cn/problem/CF140B)

# 思路

这一题的范围 $2\le n \le 300$，$O(n^3)$ 的复杂度也是可以过掉这道题的。

我们看一下思路，如果这张贺卡是原来的朋友寄过来的，自己发给自己或发不出去的话，继续循环。否则输出答案，直接退出。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tmp;
int card[1005][1005],vis[1005]; 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>card[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		cin>>tmp;
		vis[tmp]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(card[i][j]==i){
				continue;
			}
			bool flag=false;
			for(int k=1;k<card[i][j];k++){
				if(vis[k]<vis[card[i][j]]&&k!=i){
					flag=true;
				}
			}
			if(flag){
				continue;
			}
			cout<<card[i][j]<<" ";
			break;
		}
	}
	return 0;
}

```


---

## 作者：_lgh_ (赞：0)

# 思路：
对于每个朋友，枚举亚历山大可能发出的卡片，然后选出该朋友最喜欢的就可以了。站在朋友的角度想，最好的就是亚历山大寄出的卡中，自己最喜欢的。

# AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 400
int n,f[N][N],ans[N];
bool h[N];
int main()
{
  while(cin>>n)
  {
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) cin>>f[i][j];
    memset(ans,0,sizeof(ans));
    for(int i=1,x; i<=n; i++) cin>>x,ans[x]=i;
    int res[N];
    for(int i=1; i<=n; i++)
    {
      memset(h,0,sizeof(h));
      int now=-1;
      for(int j=1; j<=n; j++)
      {
        if(j==i||(now==-1 && ans[j]>ans[now])) continue;
        now=j,h[now]=1;
      }
      for(int j=1; j<=n; j++)
      {
        if(!h[f[i][j]]) continue;
        res[i]=f[i][j];
        break;
      }
    }
    for(int i=1; i<=n; i++) cout<<res[i]<<" ";
    puts("");
  }
  return 0;
}
```


---

