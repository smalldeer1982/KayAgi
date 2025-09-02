# Division and Union

## 题目描述

There are $ n $ segments $ [l_i, r_i] $ for $ 1 \le i \le n $ . You should divide all segments into two non-empty groups in such way that there is no pair of segments from different groups which have at least one common point, or say that it's impossible to do it. Each segment should belong to exactly one group.

To optimize testing process you will be given multitest.

## 说明/提示

In the first query the first and the second segments should be in different groups, but exact numbers don't matter.

In the second query the third segment intersects with the first and the second segments, so they should be in the same group, but then the other group becomes empty, so answer is $ -1 $ .

In the third query we can distribute segments in any way that makes groups non-empty, so any answer of $ 6 $ possible is correct.

## 样例 #1

### 输入

```
3
2
5 5
2 3
3
3 5
2 3
2 3
3
3 3
4 4
5 5
```

### 输出

```
2 1 
-1
1 1 2 
```

# 题解

## 作者：Austin0116 (赞：3)

# 分析
  显然，我们只要能找到两个集合间的间隔就可以确定两个集合所包含的线段。那如何确定这段间隔的位置呢？我们只需要进行按照左端点升序排序，顺序遍历，找到第一个比之前所有的线段能覆盖的最右点还要右的左端点，那么这个左端点以后的线段就是第二个集合中的线段，其余的就是第一个集合中的线段。我们只需要记录下这个左端点，再根据输入顺序再次进行排序，并判断是属于第一个集合还是第二个集合，就行了。
  
**注意：多测要清空。**

# 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,fl,mx;
struct ha{
	int x,y,id;
};
ha a[100005];
inline bool cmp1(ha &a,ha &b){//按照左端点升序排序
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
inline bool cmp2(ha &a,ha &b){//按照原来顺序排序
	return a.id<b.id;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i].x,&a[i].y);
			a[i].id=i;//记录原来位置
		} 
		sort(a+1,a+1+n,cmp1);
		mx=fl=0;//多测要清空
		for(int i=1;i<n;i++){
			mx=max(mx,a[i].y);//覆盖到的最右的端点
			if(mx<a[i+1].x){
				fl=a[i].x;//记录第一个比之前所有的线段能覆盖的最右点还要右的左端点
				break;
			} 
		} 
		sort(a+1,a+1+n,cmp2);//排序回去
		if(!fl) printf("-1");//判断无解：没有找到间隔的区间
		else for(int i=1;i<=n;i++){//判断是属于第一个集合还是第二个集合
			if(a[i].x<=fl) printf("1 ");
			else printf("2 ");
		} 
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：G_A_TS (赞：1)

题解同步发布于[blog](https://www.cnblogs.com/wzzorz/articles/10363174.html)  

------------
先按**左**端点由小到大排序，然后把线段合并为一条(能并则并)  
不能并呢？(两端点都在合并线段之外)  
那么合并线段目前长度就是断点了！(有兴趣可以证明)  
剩下的过程难度pj-  
最后上代码  

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int l;
	int r;
}edge[100010];
int T,n,nowlen,POI,yl[100010],yr[100010];//yl,yr输出用，记录原来顺序
int cmp(node a,node b)
{
	return a.l<b.l;
}
int main()
{
	cin>>T;
	for(int js=1;js<=T;js++)
	{
		POI=-1;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>edge[i].l>>edge[i].r;
			yl[i]=edge[i].l;
			yr[i]=edge[i].r;
		}
		sort(edge+1,edge+n+1,cmp);
		nowlen=edge[1].l;
		for(int i=1;i<=n;i++)
		{
			if(edge[i].r>nowlen&&edge[i].l<=nowlen)
			{
				nowlen=edge[i].r;
			}
			else
			{
				if(edge[i].r>nowlen)
				{
					POI=nowlen;
					break;
				}
			}
		}
		if(POI==-1)
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(yr[i]<=POI)
			{
				cout<<1<<" ";
			}
			else
			{
				cout<<2<<" ";
			}
		}
		cout<<endl;
	}
} 
```

---

## 作者：世末OIer (赞：1)

今天我来介绍一种不用排序的方法

```cpp
#include<bits/stdc++.h>
using namespace std;
int flag1[200005];
int flag2[200005];
set<int> use;
int x[200005],y[200005];
#define mp make_pair

//两个flag:统计每一个点上的线段的个数

inline void solve(){
	int i,j,n;
	use.clear();
	cin>>n;
	for(i=0;i<n;++i){
		cin>>x[i]>>y[i];
		++flag1[x[i]];             //头处加1，尾处减1即可  
		--flag2[y[i]+1];
		use.insert(x[i]);
		use.insert(y[i]+1);
	}
	int now;
	vector<pair<int,int> > v;
	v.clear();
	int l,r;
	bool beg=0;
	for(set<int>::iterator it=use.begin();it!=use.end();++it){
		int t=*it;
		now+=flag2[t];
		if(!now and beg){
			beg=0;
			r=t-1;
			v.push_back(mp(l,r));
		}
		now+=flag1[t];
		if(!beg){
			beg=1;
			l=t;
		}
		flag1[t]=0;
		flag2[t]=0;
	}
    //  把有交接的线段们组成一个大线段
	if(v.size()==1){
		cout<<-1<<endl;
		return;
	}
	l=v[0].first,r=v[0].second;
	for(i=0;i<n;++i) if(x[i]>=l and y[i]<=r) cout<<1<<' ';else cout<<2<<' ';
	cout<<endl;
	return;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：decoqwq (赞：1)

给你$n$条线段，问你能不能把这些线段分成两部分，使得第一部分的所有线段的并集与第二部分的所有线段的并集没有交集

我们把线段画在数轴上，可以发现，如果一个图从最左的线段到最右的线段之间都有线段连续的覆盖，即一个点要么在一个线段是但不是它的两端，或者是线段两端和其他线段的交点，那么这样肯定不能分成无交集的两部分

如果可以分，我们随便选择一个断点，前面的线段属于集合$1$，后面属于集合$2$即可

```cpp
#include <bits/stdc++.h>
using namespace std;
int l[100010],r[100010],n;
struct edge
{
    int l,r;
    bool operator<(const edge&a)const
    {
        if(l<a.l)
        {
            return 1;
        }
        else if(l>a.l)
        {
            return 0;
        }
        else
        {
            return r<a.r;
        }
    }
}e[100010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&l[i],&r[i]);
            e[i].l=l[i],e[i].r=r[i];
        }
        sort(e+1,e+n+1);
        int rr=-1;
        int flag=0;
        for(int i=1;i<=n;i++)
        {
            if(i==1)
            {
                rr=e[i].r;
                continue;
            }
            if(e[i].l>rr)
            {
                flag=1;
                break;
            }
            else
            {
                rr=max(rr,e[i].r);
            }
        }
        if(!flag)
        {
            cout<<"-1"<<endl;
            continue;
        }
        for(int i=1;i<=n;i++)
        {
            if(r[i]<=rr)
            {
                printf("1 ");
            }
            else
            {
                printf("2 ");
            }
        }
        printf("\n");
    }
}
```

---

