# The Contest

## 题目描述

Pasha 在打一场比赛，比赛共 $n$ 道题，第 $i$ 道题需要 $a_i$ 长度的时间解决，而已经被解决的题目可以在某一时刻被瞬间全部提交完成。由于评测网站收到的评测信息过多，现在只有 $m$ 个时间段是可提交的，第 $j$ 个时间段的左右端分别是 $l_j$ 和 $r_j$，请求出他能否成功提交并通过所有题目（假定他的做法永远正确）。

## 说明/提示

某次提交并不需要额外花费一个单位时间，所以样例一中的答案即为 $3+4=7$，而不需要加上若干单位时间长。

## 样例 #1

### 输入

```
2
3 4
2
1 4
7 9
```

### 输出

```
7
```

## 样例 #2

### 输入

```
1
5
1
1 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
1
5
1
1 5
```

### 输出

```
5
```

# 题解

## 作者：流绪 (赞：3)

要求提交完所有任务的最早时间，且任务不能同时进行，可以一起提交，那么我们算最晚的一个任务的提交时间就行了。

最晚一个任务结束时间就是所有任务的总时间，然后我们用这个总时间 sum 和每一个提交任务的最晚时间 b 比，如果 sum<=b,也就是说能够在这个时间内提交，那么我们比较 sum 和这个提交时间的最早时间 a，并取较大值。因为如果 a<sum 那么最早在 sum 时刻提交,如果 a>=sum,那么最早在 a 时刻提交。接下来在比较答案和这个较大值，取较小值就好了。

下面是 AC 代码，细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	int sum=0,ans = inf;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin >> x;
		sum +=x;//最晚完成任务时间
	}
	int m;
	cin >> m;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin >> a >> b;
		if(b >= sum)
			ans = min(ans,max(sum,a));更新答案
	}
	if(ans == inf)//答案未被更新,即无法合法地提交所有任务
		cout << -1;
	else
		cout << ans;
	return 0; 
}  
```


---

## 作者：zyh888 (赞：1)

# 题意
给定 pasha AC 一场比赛各题的时间，再给定 $m$ 个可提交的时间段，求 pasha AK 这场比赛最少的时间。

# 思路
- 因为可提交时间段是从小到大出现的，所以读入数无需记录，只需在线处理即可。

- 先统计 pasha 完成所有题目需要的时间，记为 $sum$。

- 读入 $m$ 组可以提交的时间段，如果其中一组可提交的时间 jj 的 $j_{l}<sum$，则在这段时间内他无法 AC 所有题目。

- 如果 $j_{r}\ge sum$，输出 $\max(sum,j_{l})$。

- 此处 $j_{l}$ 为每一段可提交时间的左端，$j_{r}$ 为每一段可提交时间的右端。 

# AC 代码
```c
#include<cstdio>
#define max(a,b) a>b?a:b
int main(){
    int n,m,sum=0,i;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&i);
        sum+=i; //pasha AK 比赛最少的时长
    }
    scanf("%d",&m);
    while(m--){
        int l,r;
        scanf("%d%d",&l,&r); //如题 每一段可提交时间的左右边界
        if(sum<=r){  //如果右边界大于 pasha AK 比赛的总时长，最优解出现了
            return !printf("%d\n",max(sum,l)); //输出最大值
        }
    }
    puts("-1"); //能爬到这里的数据都没解了
    return 0;
}
```



---

## 作者：GZY007 (赞：0)

这是一道贪心题，题目要求他完成提交所有题目的最短时间，而完成提交所有题目的时间即为最后一题提交的时间。但题目不能一起完成，所以我们只需求出完成所有题目的总时间，再和时间段比较即可。

对于每个时间段，如果时间右端点小于总时间，则最后一题的提交时间无法在这个时间段的最大限制时间提交时，即为他无法在这个时间段完成，跳过。如果总时间恰好包含此时间段里，答案即为总时间。如果时间左端点大于总时间，则最后一题只能在时间左端点提交，答案即为左端点。然后再在所有答案中找到最优解。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,sum,ans=1e9; 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		int a;
		scanf("%d",&a);
		sum+=a; 
	}
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		if(r>sum) continue ;
		ans=min(ans,max(l,sum));
	}
	if(ans!=1e9) printf("%d",ans);
	else printf("-1");
return 0;
}

```


---

