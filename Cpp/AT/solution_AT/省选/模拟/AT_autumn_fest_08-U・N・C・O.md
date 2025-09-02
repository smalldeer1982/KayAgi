# U・N・C・O

## 题目描述

[problemUrl]: https://atcoder.jp/contests/autumn_fest/tasks/autumn_fest_08



# 题解

## 作者：Porsche (赞：1)

好像还没有人来发题解，我给大家发一篇。
还有，大家可能没有看到题，链接：[H - U・N・C・O](https://autumn_fest.contest.atcoder.jp/tasks/autumn_fest_08)

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int>p[100001];
int bit[16][1<<17+1];
void add(int x,int y,int z)
{
    while(y<=1<<17)
    {
        bit[x][y]=(bit[x][y]+z)%314159265;
        y+=y&-y;
    }
}
int sum(int x,int y)
{
    int num=0;
    while(y)
    {
        num=(num+bit[x][y])%314159265;
        y-=y&-y;
    }
    return num;
}
int main()
{
    int n,d,x;
    scanf("%d%d",&n,&d);
    for(int i=0;i<n;i++)
        scanf("%d%d",&p[i].first,&p[i].second);
    sort(p,p+n);
    for(int i=0;i<n;i++)
    {
        p[i].first=p[i].second;
        p[i].second=n-i;
    }
    sort(p,p+n);
    add(0,1,1);
    for(int i=0;i<n;i++)
    {
        x=p[i].second;
        for(int j=d-1;j>=0;j--)
            add(j+1,x,sum(j,x));
    }
    cout<<bit[d][1<<17]<<endl;
    return 0;
}
```

---

