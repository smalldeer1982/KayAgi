# [USACO19JAN] Shell Game B

## 题目描述

为了消磨时光，奶牛 Bessie 和她的朋友 Elsie 喜欢玩一种她们在农业展览会上看到的游戏。

游戏准备阶段，Bessie 在桌子上放置三个倒置的坚果壳，并在其中一个坚果壳下面藏了一块小的鹅卵石（至少她希望这是一块鹅卵石——她在一块牧场的地上找到的）。随后 Bessie 会两两调换坚果壳，同时 Elsie 试着去猜鹅卵石的位置。

奶牛们在农业展览会上看到的这个游戏的标准形式是玩家可以看到鹅卵石初始的位置，然后要求玩家猜所有交换完成之后鹅卵石最终的位置。

然而，现在奶牛们想要去进行这样一种玩法，Elsie 不知道鹅卵石的初始位置，同时她可以在每一次交换之后猜一下鹅卵石的位置。Bessie 知道正确答案，在游戏结束后会给 Elsie 一个分数，等于她猜对的次数。

给定所有的交换和 Elsie 的猜测，但是不给出鹅卵石的初始位置，请求出 Elsie 最高可能获得的分数。 

## 说明/提示

### 样例解释 1

在这个例子中，Elsie 最多可以获得 $2$ 分。如果鹅卵石开始时位于坚果壳 $1$ 下面，那么她猜中了一次（最后一次）。如果鹅卵石开始时位于坚果壳 $2$ 下面，那么她猜中了两次（开始两次）。如果鹅卵石开始时位于坚果壳 $3$ 下面，那么她没有猜对任何一次。 

## 样例 #1

### 输入

```
3
1 2 1
3 2 1
1 3 1```

### 输出

```
2```

# 题解

## 作者：iostream69 (赞：10)

# 思路
这道题因为数据范围很小，所以我们可以采用暴力枚举的方式来 AC 此题。

因为坚果壳下只有两种情况（有鹅卵石或没有鹅卵石），所以我们通过布尔变量来代表坚果壳的状态。之后我们就可以通过暴力枚举的方式枚举出 Elsie 猜的每一种情况对应的分数，最后给出枚举出的最大值就可以了。

利用循环来暴力枚举，其实这道题只要数组不开小慢慢试很好 AC。

上代码！
```
#include<bits/stdc++.h>
using namespace std;
int a[101];
int b[101];
int c[101];
int q[101];//计数
bool ans[101];//布尔变量的数组千万别开小了
int main(){
    int p,x=0;
    cin>>p;
    for(int i=1;i<=p;i++)
    cin>>a[i]>>b[i]>>c[i];
    for(int k=1;k<=p;k++){//开始暴力枚举
        ans[k]=1;
        for(int j=1;j<=101;j++){//枚举Elsie会猜的答案
        swap(ans[a[j]],ans[b[j]]);//先换位
            if(ans[c[j]]==1)//如果猜对了就加1
            q[k]+=1;
        }
        for(int m=1;m<=3;m++){//清零布尔变量的值
            ans[m]=0;
        }
    }
    for(int l=1;l<=p;l++){//输出所有可能中最大值
        if(x<q[l])
        x=q[l];
    }
    cout<<x<<endl;//输出答案
    return 0;//华丽结尾
}
```

---

## 作者：T_TLucas_Yin (赞：3)

给每个杯子一个编号，在每次交换后就可以知道一个位置上是初始时的第几个杯子。

由于鹅卵石的位置只有 $3$ 种可能，所以我们大可以直接依次枚举鹅卵石初始在第 $1$ 个、第 $2$ 个、第 $3$ 个坚果壳下时，Elsie 猜对的次数。最后，取 $3$ 种情况中 Elsie 猜对最多的一种的答案输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005],b[1005],c[1005],maxn;//a[i]和b[i]是第i此操作交换的杯子位置，c[i]是第i次Elsie猜的杯子
int guess(int k){//k是鹅卵石的位置
    int f[15]={0},cnt=0;
    f[1]=1,f[2]=2,f[3]=3;
    for(int i=1;i<=n;i++){
        swap(f[a[i]],f[b[i]]);
        if(f[c[i]]==k) cnt++;//猜对了一次
    }
    return cnt;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>c[i];
    for(int i=1;i<=3;i++) maxn=max(maxn,guess(i));//三种情况
    cout<<maxn;
    return 0;
}
```

---

## 作者：1234567890sjx (赞：2)

简单题。

枚举鹅卵石的初始位置，然后暴力模拟鹅卵石的新的位置，判断一下当前猜的位置是否是鹅卵石的位置即可。

时间复杂度 $O(n^2)$。因为 $n\le 100$ 所以随便跑。

---

## 作者：Kle1N (赞：2)

考虑到只有 $3$ 个坚果壳，$N$ 也不超过 $100$，所以只需像样例解释里的那样，分别假设鹅卵石的初始位置在第 $1$、$2$、$3$ 个坚果壳下面，然后模拟题意并统计答案，最后取三个答案最大值并输出即可。

具体看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[105],b[105],g[105],cur,cnt,ans=-1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>g[i];
	}
	for(int s=1;s<=3;s++){
		cur=s;
		cnt=0;
		for(int i=1;i<=n;i++){
			if(cur==a[i])
				cur=b[i];
			else if(cur==b[i])
				cur=a[i];
			if(cur==g[i])
				cnt++;
		}
		ans=max(ans,cnt);
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：DHT666 (赞：2)

## 题意

[传送门](https://www.luogu.com.cn/problem/P9958)

三个纸杯，一个纸杯下有物品，交换 $N$ 次，每次交换两个纸杯，每次交换后有一个猜测，猜对纸杯下的物品的得分，现给出 $N$ 次交换的纸杯及猜测，求最高得分。

## 思路

考虑暴力枚举品的所在纸杯，每次按要求模拟即可，最终记录最大值为答案。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int n,ans;
int a[N],b[N],g[N];
bool now[4]; // 记录物品所在纸杯
int main() 
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i]>>b[i]>>g[i];
	}
	for(int i=1;i<=3;i++) {
		memset(now,0,sizeof now); // 初始化
		now[i] = 1;
		int tot = 0;
		for(int j=1;j<=n;j++) {
			swap(now[a[j]],now[b[j]]); // 交换纸杯
			if(now[g[j]] == 1) tot++; // 判断是否猜中
		}
		ans = max(ans,tot); // 累计最大值
	}
	cout<<ans;
	return 0;
}
~~~

完结撒花~~~

---

## 作者：n0ip (赞：2)

# P9958题解
## 题意
题目共三种情况，第一种是在第一个，第二种是在第二个，第三种是在第三个。

那么，题目给了我们这些信息，我们就可以直接写代码了。

## 思路+代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
struct node{//创建输入数组
	int a,b,g;
	
}a[105];
int shishi[5];//鹅卵石实时情况
int main(){
	int n;cin>>n;//输入个数
	for(int i=1;i<=n;i++) cin>>shishi[i].a>>shishi[i].b>>shishi[i].g;//输入每次交换情况
	int maxn=0;//定义最大值存储变量
	for(int i=1;i<=3;i++){//进行三次判断：在第一个、第二个和第三个
		int x=0;//这一次的次数
		w[i]=1;
		for(int j=1;j<=n;j++){//进行判断
			swap(w[shishi[j].a],w[shishi[j].b]);//进行交换
			if(w[shishi[j].g]==1) x++;//如果猜中就增加，否则不变
		}
		maxn=max(x,maxn);//判断最大值
		memset(w,0,sizeof w);//清空数组函数（memset）
	}
	cout<<maxn;//输出最大值
	return 0;
}
```
最后说一下个人看法：其实这道题不算太难，跟着题意写代码就行了，也不用什么过于高深的函数，只要仔细点，都是可以做出来的。

---

## 作者：2023gdgz01 (赞：2)

一道基础模拟题。

具体地说，我们可以分别计算鹅卵石在编号为 $1,2,3$ 的坚果壳下的情况后取最大值即可，可参考注释理解。时间复杂度 $O(n)$。

代码如下：

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

int n, a[105], b[105], g[105];

inline int cal(int p) { //计算鹅卵石在编号为 p 的坚果壳时的分数
	int res = 0;
	int pos[4] = {0, 1, 2, 3}; //pos[i] 表示坚果壳 i 原始的位置
	for (register int i = 1; i <= n; ++i) {
		swap(pos[a[i]], pos[b[i]]); //交换
		if (pos[g[i]] == p)
			++res;
	}
	return res;
}

int main() {
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%d%d%d", a + i, b + i, g + i);
	printf("%d", max(max(cal(1), cal(2)), cal(3)));
	return 0;
}
```

[AC 链接](https://www.luogu.com.cn/record/140089402)

---

## 作者：Yuki_Ever (赞：0)

# solve
容易看出，当一开始鹅卵石的位置确定后，以后每次交换之后鹅卵石的位置都是固定的。因此考虑分别枚举刚开始时鹅卵石在三个坚果壳中的哪一个，依次计算在每种情况下的得分数，最后取最大值即可。

我们可以建立三个布尔数组，分别对应最开始时鹅卵石的三种位置。

对于每个数组，将鹅卵石所处位置标记为 $1$，其他位置标记为 $0$。

对于每次交换，直接将两个位置的标记值换一下就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int q;
bool stone1[4],stone2[4],stone3[4];		//三种情况
int score1,score2,score3;
int main() {
	scanf("%d",&q);
	int a,b,g;
	stone1[1]=1,stone2[2]=1,stone3[3]=1;	//刚开始时石头的位置
	while(q--){
		scanf("%d%d%d",&a,&b,&g);
		swap(stone1[a],stone1[b]);	//换位置
		swap(stone2[a],stone2[b]);
		swap(stone3[a],stone3[b]);
		if(stone1[g]==1)score1++;	//判得分
		if(stone2[g]==1)score2++;
		if(stone3[g]==1)score3++;
	}					//取最大值
	cout<<max(max(score1,score2),score3)<<endl;
	return 0;
} 
```


---

## 作者：watergod (赞：0)

# P9958 [USACO19JAN] Shell Game B 题解

[题目传送门](https://www.luogu.com.cn/problem/P9958)

这题难度约为橙。

## 题目分析

题目大意就是有 $3$ 个杯子，其中一个杯子下面有球，给定 $N$ 次交换，每次交换后可以猜测一次球在哪里，求猜对的最多次数。

很明显，题目就 $3$ 个杯子，我们只需要依次枚举，判断最开始时球在 $3$ 个杯子中的哪一个，对于每一种情况，按照题意模拟交换，计算出猜对的次数，最后比较三者之间的最大值即可。

结合代码注释。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n;
long long ans;
long long solve_ans;
long long a[114514],b[114514],g[114514];

long long solve(long long wz){
	solve_ans = 0;
	for(register int i=1;i<=n;i++){
		// 交换 
		if(wz == a[i]){
			wz = b[i];
		}else if(wz == b[i]){
			wz = a[i];
		}
		// 计算是否猜对了  
		if(wz == g[i]){
			solve_ans++;
		}
	}
	return solve_ans;
}

int main(){
	cin >> n;
	for(register int i=1;i<=n;i++){
		cin >> a[i] >> b[i] >> g[i];
	}
	// 依次判断在三个杯子中的情况  
	for(register int i=1;i<=3;i++){
		ans = max(ans,solve(i));
	}
	cout << ans << endl;
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/140605337)

---

