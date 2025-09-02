# Mittens

## 题目描述

A Christmas party in city S. had $ n $ children. All children came in mittens. The mittens can be of different colors, but each child had the left and the right mitten of the same color. Let's say that the colors of the mittens are numbered with integers from 1 to $ m $ , and the children are numbered from 1 to $ n $ . Then the $ i $ -th child has both mittens of color $ c_{i} $ .

The Party had Santa Claus ('Father Frost' in Russian), his granddaughter Snow Girl, the children danced around the richly decorated Christmas tree. In fact, everything was so bright and diverse that the children wanted to wear mittens of distinct colors. The children decided to swap the mittens so that each of them got one left and one right mitten in the end, and these two mittens were of distinct colors. All mittens are of the same size and fit all the children.

The children started exchanging the mittens haphazardly, but they couldn't reach the situation when each child has a pair of mittens of distinct colors. Vasily Petrov, the dad of one of the children, noted that in the general case the children's idea may turn out impossible. Besides, he is a mathematician and he came up with such scheme of distributing mittens that the number of children that have distinct-colored mittens was maximum. You task is to repeat his discovery. Note that the left and right mittens are different: each child must end up with one left and one right mitten.

## 样例 #1

### 输入

```
6 3
1 3 2 2 1 1
```

### 输出

```
6
2 1
1 2
2 1
1 3
1 2
3 1
```

## 样例 #2

### 输入

```
4 2
1 2 1 1
```

### 输出

```
2
1 2
1 1
2 1
1 1
```

# 题解

## 作者：_HMZ_ (赞：0)

感谢初二大佬 [Allanljx](https://www.luogu.com.cn/user/406947) 的指点。

## 题目大意：

有 $n$ 个人，每个人有一双手套，且两个人之间可以互相换。

注意，只能左手换左手，右手换右手。

求最多有几个人的手套不同色并输出任意一种方案。

## 解题思路：

首先，最多有几个人很好求出，假设当前某一颜色出现次数最多的值为 $w$。

如果 $w$ 小于等于 $n$，则可以让前半部分的人都穿左手，其余的都穿右手。

这样出现次数最多的就分完了，其余手套随便分即可，这样一来所有人的手套颜色都不一样。

否则 $w$ 大于 $n$，必须要有某些人的手套颜色相同。

还是跟刚才一样，先让前 $w$ 个人穿左手，再让后 $w$ 个人穿右手。

这样最多的人就是 $2 \times n - w$。

考虑方案，对于第 $i$ 个人，如果他的手套已经不同色，则不用交换。

否则，找另一个人，如果交换之后第 $i$ 和第 $j$ 个人的手套都能不同色，就交换。

## AC代码：

```cpp
#include<iostream>
using namespace std;
int n,m,x[10005],y[10005],cnt[10005],maxx;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        y[i]=x[i];
        cnt[x[i]]+=2;//注意是一双手套，实际有两只。
        maxx=max(maxx,cnt[x[i]]);//统计上文的w。
    }
    if(maxx<=n)
        cout<<n<<endl;
    else
        cout<<2*n-maxx<<endl;
    for(int i=1;i<=n;i++)
    {
        if(x[i]!=y[i])  continue;//当前枚举到的人手套已经不同色，则不交换。
        for(int j=1;j<=n;j++)
        {
            if(x[j]!=y[i] && x[i]!=y[j])//交换之后两人都能手套不同色。
                swap(x[i],x[j]);
            else if(x[i]!=y[j] && x[j]!=y[i])
                swap(y[i],y[j]);
        }
    }
    for(int i=1;i<=n;i++)
        cout<<x[i]<<' '<<y[i]<<endl;
    return 0;
}
```


---

## 作者：Allanljx (赞：0)

## 思路
如果某一种颜色的手套数量大于 $n$ 就会有拿到相同颜色的手套的人，假设对于某颜色有最多的手套且数量为 $maxn$，那么如果 $maxn\leq n$ 则所有人的都能拿到不同颜色的手套，否则就只有 $2\times n-maxn$ 个人可以拿到不同颜色的的手套。然后暴力枚举任意两个人判断如果交换后可以满足手套颜色不一样就交换。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[5005],sum[105],maxn;
int l[5005],r[5005];//l表示左手的颜色，r表示右手的颜色
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		l[i]=r[i]=a[i];
		sum[a[i]]+=2;
		maxn=max(maxn,sum[a[i]]);//某一颜色的数量
	}
	if(maxn<=n) printf("%d\n",n);
	else printf("%d\n",2*n-maxn);
	for(int i=1;i<=n;i++)//暴力交换
	{
		if(l[i]!=r[i]) continue;
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			if(l[i]!=r[j]&&l[j]!=r[i]) swap(l[i],l[j]);//交换左手
			else if(l[j]!=r[i]&&l[i]!=r[j]) swap(r[i],r[j]);//交换右手
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d %d\n",l[i],r[i]);//最终颜色
	}
}
```

---

