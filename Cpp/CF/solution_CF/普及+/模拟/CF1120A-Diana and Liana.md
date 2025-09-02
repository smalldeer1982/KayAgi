# Diana and Liana

## 题目描述

Shortriver 镇举办了传统的花卉节。小镇上的居民们在节日期间都会佩戴有 $k$ 朵花的花环。共 $n$ 位居民每人都会得到一个花环。

有一条藤蔓，上面有 $m$ 朵花，这条藤蔓是一个序列 $a$，$a_i$ 表示第 $i$ 朵花的类型。有一台机器来切割这条藤蔓，它会一直切下藤蔓前端的 $k$ 朵花，直到剩下的花数量不足 $k$。

Diana 制作了一个花环示意图，是一个长度为 $s$ 的序列 $b$。Diana 要按照这个示意图制作一个花环，要求机器切割下来的花环至少有一个包含序列 $b$ 里所有类型的花。**如果一种类型的花在此序列中出现多次，则该类型的花朵数量至少应为该序列中该花的出现次数。花朵的顺序无关紧要。**

为了制作这个花环，Diana 可以取下藤蔓上的一些花朵，但又要保证每个居民都能得到一个花环（**Diana 自己也算一位居民**）。请给出一种取下花朵的方案。

## 样例 #1

### 输入

```
7 3 2 2
1 2 3 3 2 1 2
2 2
```

### 输出

```
1
4 
```

## 样例 #2

### 输入

```
13 4 3 3
3 2 6 4 1 4 4 7 1 3 3 2 4
4 3 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
13 4 1 3
3 2 6 4 1 4 4 7 1 3 3 2 4
4 3 4
```

### 输出

```
9
1 2 3 4 5 9 11 12 13
```

# 题解

## 作者：周小涵 (赞：7)

### 题目大意

一共有 $m$ 朵花，$k$ 朵花可以串成一个花环，需要制作 $n$ 个花环，其中一个花环要满足含有给出的   $s$ 朵花的序列（顺序可不同）。问删去多少朵花可以满足上述条件并输出删除花的位置。


### 题目分析

- 记录在 $s$ 中每个数据出现的次数以及是否出现过。遍历 $m$ 朵花，如果当前位置数据出现在 $s$ 中，则将此处记为开始位置，更新记录的 $s$ 中每个数据出现的次数，即将当前位数据出现次数减一，并将 $s$ 减一。之后继续向下遍历，每当遇到出现 $s$ 中的数据，将进行下述操作：



	1 .将当前位数据出现次数减一，将该位置记为结束位置。

	2 .如果更新前当前位数据出现次数大于 $0$ ，则将 $s$ 减一。


- 判断开始位置的数据是否与该位置相同，如果相同则将开始位置后延，并将该数据出现次数加一，直到当前开始位置出现过并且当前开始位置数据出现次数不小于零。


- 如果 $s$ 等于 $0$ 时，说明我们取的区间已经包含了 $s$ 序列中的全部数据。由于一个花环只有 $k$ 朵花，在当前起始位置前可以制作成最多整个花环的最后一位的下一位即可将其当作包含 $s$ 的起始位置，在当前结束位置后可以制作成最多整个花环的第一位的前一位当作包含 $s$ 的结束位置，如果此时可以制作出 $n$ 个花环及其以上，则满足题意，记录此时的起止位置。

- 要去除的数量就是 $m - n\times k$ 个。若起始位置之前就可以制作 $n - 1$ 个花环即从制作好 $n - 1$ 个花环的后一位开始输出直到起始位置（不输出起始位置）。输出起止位置中间除去 $s$ 中的数字之外的前 $ ansen - ansbe + 1 - k$ 个数的位置。最后输出终止位置后剩余需要输出的位置即可。


### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int num[500100],vis[500100],mp[500100],removenum;
void print(int x){
    printf("%d",x);
    if(removenum>1) printf(" ");
    removenum--;
}
int main()
{
    int m,k,n,s;
    scanf("%d%d%d%d",&m,&k,&n,&s);
    for(int i=1;i<=m;i++) scanf("%d",&num[i]);
    for(int i=1;i<=s;i++){
        int tmp;
        scanf("%d",&tmp);
        mp[tmp]++;
        vis[tmp]++;
    }
    int be=-1,en=-1,sum=s,ansbe=-1,ansen=-1;
    for(int i=1;i<=m;i++){
        if(mp[num[i]]>0){
            if(sum==s) be=i;
            if(sum>0) sum--;
        }
        if(vis[num[i]]){
            mp[num[i]]--;
            en=i;
        }
        while((mp[num[be]]==0&&vis[num[be]]==0)||(mp[num[be]]<0&&vis[num[be]])){
            if(be+1>m) break;
            if(mp[num[be]]<0) mp[num[be]]++;
            be++;
        }
        if(sum==0&&en!=-1&&be!=-1&&(((be-1)/k+(m-max(en,((be-1)/k+k)-1))/k+1)>=n)){
            ansbe=(be-1)/k*k+1;
            ansen=max(en,(be-1)/k+k);
        }
    }
    if(ansbe!=-1&&ansen!=-1){
        ansen=max(ansen,ansbe+k-1);
        removenum=m-n*k;
        printf("%d\n",removenum);
        int i=1;
        for(i=(n-1)*k+1;i<ansbe;i++){
            print(i);
        }
        int cnt=ansen-ansbe+1-k;
        for(int i=ansbe;i<=ansen;i++){
            if(vis[num[i]]) vis[num[i]]--;
            else{
                if(cnt){
                    print(i);cnt--;
                }
            }
        }
        for(i=ansen+1;i<=m;i++){
            if(removenum){
                print(i);
            }
        }
        printf("\n");
    }
    else{
        printf("-1\n");
    }
    return 0;
}

```


---

## 作者：Inui_Sana (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1120A)

解题思路：贪心+双指针

题面有一点长，但看完后，很容易想到，就是在 $a$ 中找包含 $b$ 的一个子段。很明显，如果子段 $[l,r]$ 满足要求，那 $[l,r+1]$ 肯定也满足要求，满足单调性。可以用双指针或二分来维护。之前这种题一直用的二分，这里就用一次双指针吧。

找出这个区间后，看剩下的花能不能组成足够的花环。要注意组成花环的花一定是连续的，所以除了这个区间之内要取下一些花，区间前也要取下一些，随便取都行，区间后就不用理会了。

code：

```cpp
int n,m,k,num,sum,cnt,e[maxn],nd[maxn],box[maxn];
vector<int> ans;
inline void add(int x){//用了点类似莫队的操作
	box[x]++;
	if(box[x]==nd[x])cnt++;
}
inline void del(int x){
	if(box[x]==nd[x])cnt--;
	box[x]--;
}
void solve(){
	scanf("%d%d%d%d",&n,&k,&num,&m);
	for(int i=1;i<=n;i++)scanf("%d",&e[i]);
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		sum+=!nd[x];
		nd[x]++;
	}
	for(int l=1,r=0;l<=n-k+1;del(e[l++])){
		while(r<l+k-1)add(e[++r]);
		while(r<n&&cnt<sum)add(e[++r]);
		if(cnt<sum)printf("-1"),exit(0);
		if((l-1)/k+(n-r)/k>=num-1){
			int len=r-l+1;
			for(int j=(l-1)/k*k+1;j<l;j++)ans.pb(j);//删去一些区间前的数
			for(int j=l;j<=r;j++){
				if(nd[e[j]])nd[e[j]]--;
				else if(len>k)ans.pb(j),len--;
			}
			printf("%d\n",ans.size());
			for(int j=0;j<ans.size();j++)printf("%d ",ans[j]);
			return;
		}
	}
	printf("-1");
}
```

---

