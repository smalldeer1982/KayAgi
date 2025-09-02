# 题目信息

# [USACO12FEB] Overplanting S

## 题目描述

Farmer John has purchased a new machine that is capable of planting grass within any rectangular region of his farm that is "axially aligned" (i.e., with vertical and horizontal sides).  Unfortunately, the machine malfunctions one day and plants grass in not one, but N (1 <= N <= 1000) different rectangular regions, some of which may even overlap.

Given the rectangular regions planted with grass, please help FJ compute the total area in his farm that is now covered with grass.

在一个笛卡尔平面坐标系里（则 $X$ 轴向右是正方向，$Y$ 轴向上是正方向），有 $N\ (1 \le N \le 1000)$ 个矩形，第 $i$ 个矩形的左上角坐标是 $(x_1,y_1)$，右下角坐标是 $(x_2,y_2)$。问这 $N$ 个矩形所覆盖的面积是多少？

注意：被重复覆盖的区域的面积只算一次。

## 样例 #1

### 输入

```
2
0 5 4 1
2 4 6 2
```

### 输出

```
20```

# AI分析结果

### 综合分析与结论
这些题解主要围绕计算多个矩形覆盖面积这一问题展开，提供了多种解题思路，包括扫描线、矩形切割、差分与前缀和、线段覆盖等。扫描线算法结合离散化与线段树，能高效处理区间修改和查询；矩形切割则通过不断切割矩形来避免重复计算；差分与前缀和利用数组记录覆盖次数，最后计算面积。各算法在思路清晰度、代码复杂度和时间复杂度上有所差异。

### 所选题解
- **作者：Ofnoname (赞：59)，5星**
  - **关键亮点**：思路清晰，详细介绍了扫描线算法的原理和实现步骤，结合离散化和线段树，高效处理区间修改和查询。
  - **个人心得**：提到代码开 `O2` 会 `WA`，需开更大空间，提醒注意线段树空间问题。
- **作者：山蛙or山兔 (赞：46)，4星**
  - **关键亮点**：代码简洁，通过排序和维护最低顶边、底边来计算面积，思路直观。
- **作者：Shik__Utau (赞：36)，4星**
  - **关键亮点**：详细介绍了矩形切割的思想和实现方法，通过不断切割矩形避免重复计算。

### 重点代码与核心实现思想
#### Ofnoname的题解
```cpp
struct Node { int x, y0, y1, c; } a[MAX];
int cmp(Node a, Node b) { return a.x < b.x; }

unordered_map <int, int> H;

int N, M, qy[MAX];
long long ans;

struct Segtree
{
    #define i0 (i << 1)
    #define i1 (i << 1 | 1)
    int L[MAX << 2], R[MAX << 2], v[MAX << 2], len[MAX << 2];
    void init(int i, int l, int r)
    {
        L[i] = l, R[i] = r, v[i] = len[i] = 0;
        if (l != r) {
            int mid = l + r >> 1;
            init(i0, l, mid), init(i1, mid+1, r);
        }
    }
    void add(int i, int l, int r, int c)
    {
        if (r < L[i] || R[i] < l) return;
        if (l <= L[i] && R[i] <= r)
            v[i] += c;
        else add(i0, l, r, c), add(i1, l, r, c);
        if (v[i]) len[i] = qy[R[i]+1] - qy[L[i]];
        else len[i] = len[i0] + len[i1];
    }
} Seg;

int main()
{
    scanf("%d", &N), H.clear();
    for (int i = 1, x0, y0, x1, y1; i <= N; i++)
    {
        scanf("%d%d%d%d", &x0, &y1, &x1, &y0);
        a[i] = Node{x0, y0, y1, 1};
        a[i+N] = Node{x1, y0, y1, -1};
        qy[++M] = y0, qy[++M] = y1;
    }
    sort(qy+1, qy + M+1), M = unique(qy+1, qy + M+1) - qy - 1;
    for (int i = 1; i <= M; i++)
        H[qy[i]] = i;
    
    Seg.init(1, 1, (N <<= 1));
    sort(a + 1, a + N + 1, cmp);
    for (int i = 1; i <= N; i++)
    {
        Seg.add(1, H[a[i].y0], H[a[i].y1] - 1, a[i].c);
        ans += (long long)Seg.len[1] * (a[i+1].x - a[i].x);
    } printf("%lld\n", ans);
}
```
**核心实现思想**：将 `y` 坐标离散化，用一根竖直的线从左向右扫描，遇到矩形的竖边时更新线段树，统计被覆盖的长度，乘以相邻竖边的 `x` 坐标差得到小矩形的面积，累加得到总面积。

#### 山蛙or山兔的题解
```cpp
long long n,x[maxn],y[maxn],x2[maxn],y2[maxn],side[2*maxn];
int arr[maxn];
long long ans;

bool cmp(int a,int b)
{
    return y[a]>y[b];
}

int main()
{
    cin >> n;
    for (int i=0;i<n;i++) 
    {
        cin >> x[i] >> y[i] >> x2[i] >> y2[i];
        side[2*i]=x[i];
        side[2*i+1]=x2[i];
    }
    sort(side,side+2*n);
    ans=0;
    for (int i=1;i<2*n;i++)
    {
        if (side[i-1]==side[i]) continue;
        int m=0;
        for (int j=0;j<n;j++)
        {
            if (x[j]<=side[i-1] && side[i]<=x2[j]) arr[m++]=j;
        }
        sort(arr,arr+m,cmp);
        long long h=y[arr[0]],d=y2[arr[0]],w=side[i]-side[i-1];
        for (int j=1;j<m;j++)
        {
            int temp=arr[j];
            if (y[temp]>d)
            {
                ans+=(h-y[temp])*w;
                h=y[temp];
            }
            else
            {
                ans+=(h-d)*w;
                h=y[temp];
            }
            if (y2[temp]<d) d=y2[temp];
        }
        ans+=(h-d)*w;
    }
    cout << ans << endl;
}
```
**核心实现思想**：将所有竖线排序，遍历竖线，将两条竖线都穿过的长方形加入数组，按顶边排序，维护最低顶边和底边，更新答案。

#### Shik__Utau的题解
```cpp
struct node{ll x1,y1,x2,y2;}a[maxn];
int n,tot=0;
void Add(ll x1,ll y1,ll x2,ll y2){a[++tot]=(node){x1,y1,x2,y2};}
void Cut(int p,ll x1,ll y1,ll x2,ll y2,int cmd){
    ll k1,k2;
    if(!cmd){
        k1=max(x1,a[p].x1);
        k2=min(x2,a[p].x2);
        if(a[p].x1<k1)Add(a[p].x1,a[p].y1,k1,a[p].y2);
        if(k2<a[p].x2)Add(k2,a[p].y1,a[p].x2,a[p].y2);
        Cut(p,k1,y1,k2,y2,1);
    }
    else{
        k1=min(y1,a[p].y1);
        k2=max(y2,a[p].y2);
        if(a[p].y1>k1)Add(x1,a[p].y1,x2,k1);
        if(k2>a[p].y2)Add(x1,k2,x2,a[p].y2);
    }
}
int main(){
    scanf("%d",&n);
    ll x1,y1,x2,y2;
    scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
    Add(x1,y1,x2,y2);
    for(int i=2;i<=n;i++){
        scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
        for(int j=1;j<=tot;j++){
            if(a[j].x1>=x2||a[j].x2<=x1||a[j].y1<=y2||a[j].y2>=y1)continue;
            Cut(j,x1,y1,x2,y2,0);
            a[j]=a[tot];
            tot--;j--;
        }
        Add(x1,y1,x2,y2);
    }
    ll ans=0;
    for(int i=1;i<=tot;i++)ans+=(a[i].x2-a[i].x1)*(a[i].y1-a[i].y2);
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：用当前矩形去切割之前所有加入的矩形，将它们分成更多小矩形，删除原矩形，最后加入当前矩形，计算所有矩形的面积和。

### 最优关键思路或技巧
- **离散化**：处理坐标范围较大的问题，将坐标映射到较小的范围内，减少空间复杂度。
- **扫描线**：用一根线扫描图形，将复杂的二维问题转化为一维问题，结合线段树高效处理区间修改和查询。
- **矩形切割**：通过不断切割矩形，避免重复计算，将不规则图形转化为多个小矩形。

### 可拓展之处
- **同类型题**：计算多个矩形的交集面积、计算多个矩形的周长等。
- **类似算法套路**：扫描线算法可用于处理区间覆盖、区间查询等问题；矩形切割可用于处理图形的合并、分割等问题。

### 推荐题目
- P1496 火烧赤壁：线段覆盖问题，可作为本题的基础练习。
- P1884 [USACO12FEB] Overplanting S：本题原题，可进一步巩固解题思路。
- P5490 【模板】扫描线：扫描线算法的模板题，可加深对扫描线算法的理解。

### 个人心得总结
- Ofnoname：代码开 `O2` 会 `WA`，需注意线段树空间问题。
- 顾z：没开 `long long` 导致没一遍切题，提醒注意数据范围。

---
处理用时：73.41秒