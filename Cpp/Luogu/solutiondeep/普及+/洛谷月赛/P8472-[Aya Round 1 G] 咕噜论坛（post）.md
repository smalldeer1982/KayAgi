# 题目信息

# [Aya Round 1 G] 咕噜论坛（post）

## 题目描述

「咕噜论坛」的一篇帖子下，有若干个不同的人对其进行了回复，这些评论形成了一个 $n\times m$ 的矩阵。

论坛管理员 prAB 发现这些评论者的名字颜色只有灰名、紫名和棕名三种，他决定「动用神权」来增加这些评论的整齐度。但是论坛站长超氧化铯（CsO2）可能会因为他「滥用神权」导致论坛「臭名昭著」而踢掉他的管理身份。所以 prAB **最多**只能动用 $k$ 次神权。已知他的神权有两种：

- 「暴政警告」：送一个灰名进陶片使他变成棕名。
- 「放人一马」：将一个棕名解封使他变成灰名。

由于「咕噜论坛」的管理员是至高无上的，对于评论中的紫名他无能为力。

prAB 认为在这些评论者的名字颜色中，最大的颜色相同的子矩阵的大小能代表这篇帖子评论的整齐度。所以他想知道，他动用完神权后评论的整齐度的最大值。

## 说明/提示

### 数据范围及约定

对于 $100\%$ 的数据，$1 \le n,m\le 500$，$0 \le k \le nm$。字符矩阵中只会出现大写字母 `B`、`G` 和 `P`。

## 样例 #1

### 输入

```
3 4 2
BBGB
GBBB
PGPP```

### 输出

```
8
BBBB
BBBB
PGPP```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均是通过二维前缀和优化对矩阵子区域的统计，并利用双指针法优化枚举过程，从而找到满足条件的最大同色子矩阵。主要难点在于如何合理利用前缀和与双指针降低时间复杂度，以及对紫名情况的特殊处理。

### 所选的题解
- **作者：chen_zhe (赞：14)  星级：5星**
    - **关键亮点**：思路清晰，先预处理出G和P的二维前缀和，通过枚举子矩阵的第一行和最后一行，利用二维前缀和差分判断能否用神权使子矩阵颜色相同，再用双指针计算最大整齐度，同时考虑了全紫名矩阵的特殊情况，代码结构清晰，逻辑严谨。
    - **个人心得**：无
    - **核心代码**：
```cpp
bool check1(int xl,int xr,int yl,int yr)
{
    if(cnt[xr][yr]-cnt[xr][yl-1]-cnt[xl-1][yr]+cnt[xl-1][yl-1]>0)
        return 0;
    if(sum[xr][yr]-sum[xr][yl-1]-sum[xl-1][yr]+sum[xl-1][yl-1]<=k)
        return 1;
    if(sum[xr][yr]-sum[xr][yl-1]-sum[xl-1][yr]+sum[xl-1][yl-1]>=(xr-xl+1)*(yr-yl+1)-k)
        return 1;
    return 0;
}
bool check2(int xl,int xr,int yl,int yr)
{
    if(cnt[xr][yr]-cnt[xr][yl-1]-cnt[xl-1][yr]+cnt[xl-1][yl-1]==(xr-xl+1)*(yr-yl+1))
        return 1;
    else
        return 0;
}
int main()
{
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++)
    {
        cin >> (s[i]+1);
        for(int j=1;j<=m;j++)
        {
            sum[i][j]=sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+(s[i][j]=='G');
            cnt[i][j]=cnt[i][j-1]+cnt[i-1][j]-cnt[i-1][j-1]+(s[i][j]=='P');
        }
    }
    for(int yl=1;yl<=m;yl++)
    {
        for(int yr=yl;yr<=m;yr++)
        { 
            int l=1,r=0;
            while(r<=n && l<=n)
            {
                while(r<n && check1(l,r+1,yl,yr))
                    r++;
                if((yr-yl+1)*(r-l+1)>ans)
                {
                    ansxl=l;
                    ansxr=r;
                    ansyl=yl;
                    ansyr=yr;
                    ans=(yr-yl+1)*(r-l+1);
                }
                l++;
            }
        }
    }
    for(int yl=1;yl<=m;yl++)
    {
        for(int yr=yl;yr<=m;yr++)
        { 
            int l=1,r=0;
            while(r<=n && l<=n)
            {
                while(r<n && check2(l,r+1,yl,yr))
                    r++;
                if((yr-yl+1)*(r-l+1)>ans)
                {
                    ansxl=l;
                    ansxr=r;
                    ansyl=yl;
                    ansyr=yr;
                    ans=(yr-yl+1)*(r-l+1);
                }
                l++;
            }
        }
    }
    // 输出部分代码省略
    return 0;
}
```
    - **核心思想**：`check1`函数判断子矩阵能否通过神权操作变为同色（非紫色），`check2`函数判断子矩阵是否全为紫色。在`main`函数中，先预处理前缀和，然后通过双重循环枚举子矩阵的上下边界，利用双指针在列方向上寻找满足条件的最大子矩阵。

- **作者：KingPowers (赞：8)  星级：4星**
    - **关键亮点**：先阐述暴力做法及复杂度，再点明优化思路，即通过减少枚举信息，仅枚举子矩阵的上下两行并用双指针处理左右边界，降低时间复杂度。代码通过多个`check`函数判断子矩阵能否变为某种颜色，逻辑较清晰。
    - **个人心得**：无
    - **核心代码**：
```cpp
inline bool check_B(int ax,int ay,int bx,int by){  //能否全棕
    int SB=sumb[bx][by]-sumb[bx][ay-1]-sumb[ax-1][by]+sumb[ax-1][ay-1];
    int SP=sump[bx][by]-sump[bx][ay-1]-sump[ax-1][by]+sump[ax-1][ay-1];
    if(SP) return 0;  //如上所述
    if((bx-ax+1)*(by-ay+1)-SB<=k) return 1;
    return 0;
}
inline bool check_G(int ax,int ay,int bx,int by){  //能否全灰
    int SG=sumg[bx][by]-sumg[bx][ay-1]-sumg[ax-1][by]+sumg[ax-1][ay-1];
    int SP=sump[bx][by]-sump[bx][ay-1]-sump[ax-1][by]+sump[ax-1][ay-1];
    if(SP) return 0;  //如上所述
    if((bx-ax+1)*(by-ay+1)-SG<=k) return 1;
    return 0;
}
inline bool check_P(int ax,int ay,int bx,int by){  //能否全紫
    int SP=sump[bx][by]-sump[bx][ay-1]-sump[ax-1][by]+sump[ax-1][ay-1];
    if(SP==(bx-ax+1)*(by-ay+1)) return 1;  //如上所述
    return 0;
}
signed main(){
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++){
        scanf("%s",mp[i]+1);
        for(int j=1;j<=m;j++){  //预处理前缀和
            sumb[i][j]=sumb[i-1][j]+sumb[i][j-1]-sumb[i-1][j-1]+(mp[i][j]=='B');
            sumg[i][j]=sumg[i-1][j]+sumg[i][j-1]-sumg[i-1][j-1]+(mp[i][j]=='G');
            sump[i][j]=sump[i-1][j]+sump[i][j-1]-sump[i-1][j-1]+(mp[i][j]=='P');
        }
    }
    for(int i=1;i<=n;i++)  //全变棕
        for(int j=i;j<=n;j++)
            for(int l=1,r=0;l<=n&&r<=n;l++){
                while(r<m&&check_B(i,l,j,r+1)) r++; 
                if((r-l+1)*(j-i+1)>mx){  //整齐度更高就更新答案
                    mx=(r-l+1)*(j-i+1);
                    ans1=i,ans2=l,ans3=j,ans4=r,ansc='B';
                }
            }
    // 全变灰和全紫的枚举过程类似，代码省略
    return 0;
}
```
    - **核心思想**：通过`check_B`、`check_G`、`check_P`函数分别判断子矩阵能否变为棕色、灰色、紫色。在`main`函数中，先预处理三种颜色的前缀和，然后分别枚举上下边界，利用双指针在列方向上寻找能变为某种颜色且整齐度最高的子矩阵。

- **作者：chenzefan (赞：3)  星级：4星**
    - **关键亮点**：先点明暴力做法会超时，引出优化思路为二维前缀和结合双指针算法。代码通过`check`函数判断子矩阵是否满足要求，分别对棕名、灰名、紫名情况进行枚举，逻辑较清晰，注释详细。
    - **个人心得**：无
    - **核心代码**：
```cpp
bool check(int i,int l,int j,int r,char c){
    int S,SP;
    if(c=='B') S=sum_B[j][r]-sum_B[j][l-1]-sum_B[i-1][r]+sum_B[i-1][l-1];//考虑棕名
    if(c=='G') S=sum_G[j][r]-sum_G[j][l-1]-sum_G[i-1][r]+sum_G[i-1][l-1];//考虑灰名
    SP=sum_P[j][r]-sum_P[j][l-1]-sum_P[i-1][r]+sum_P[i-1][l-1];//紫名每次都要考虑 
    if(SP!=0&&c!='P') return 0;//矩阵内出现紫名，并且此时不考虑紫名，那么返回0
    if(c=='P'&&(j-i+1)*(r-l+1)==SP) return 1;
    if((j-i+1)*(r-l+1)-S<=k&&c!='P') return 1;//如果最多用k次能做到要求，那么返回1
    return 0;//做不到要求，返回0 
}
signed main(){//因为用 int 代替了 long long ，所以这里改成 signed 
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            sum_B[i][j]=sum_B[i-1][j]+sum_B[i][j-1]-sum_B[i-1][j-1]+(a[i][j]=='B');//计算从(1,1)到(i,j)这个矩阵中有多少个棕名 
            sum_G[i][j]=sum_G[i-1][j]+sum_G[i][j-1]-sum_G[i-1][j-1]+(a[i][j]=='G');//计算从(1,1)到(i,j)这个矩阵中有多少个灰名 
            sum_P[i][j]=sum_P[i-1][j]+sum_P[i][j-1]-sum_P[i-1][j-1]+(a[i][j]=='P');//计算从(1,1)到(i,j)这个矩阵中有多少个紫名 
        }
    //考虑棕色
    for(int i=1;i<=n;i++) 
        for(int j=i;j<=n;j++){
            int l=1,r=0;
            while(l<=m&&r<=m){
                while(r<m&&check(i,l,j,r+1,'B')) r++; 
                if((r-l+1)*(j-i+1)>maxx){
                    maxx=(r-l+1)*(j-i+1);//更新矩阵大小 
                    ans1=i,ans2=l,ans3=j,ans4=r,ans_char='B';//更新矩阵范围以及颜色，方便输出  
                }
                l++; 
            }
        } 
    //考虑灰色和紫色的枚举过程类似，代码省略
    return 0;
}
```
    - **核心思想**：`check`函数根据传入的颜色判断子矩阵是否满足变为该颜色的条件。在`main`函数中，先预处理三种颜色的前缀和，然后分别枚举上下边界，利用双指针在列方向上寻找满足条件且面积最大的子矩阵。

### 最优关键思路或技巧
- **二维前缀和优化统计**：通过预处理二维前缀和，能够在 $O(1)$ 时间内获取子矩阵内每种颜色的数量，大大减少了重复计算。
- **双指针优化枚举**：利用子矩阵右边界随左边界递增的性质，使用双指针法在固定上下边界后，在列方向上高效地寻找满足条件的最大子矩阵，将原本 $O(n^2m^2)$ 的暴力枚举复杂度降低到 $O(n^3)$ 或 $O(nm^2)$。
- **特殊情况处理**：对紫名情况进行特殊判断，确保在考虑将子矩阵变为灰色或棕色时，子矩阵内无紫名；同时单独判断子矩阵是否全为紫名。

### 可拓展思路
此类题目属于矩阵类优化枚举问题，常见拓展方向为增加矩阵操作类型、改变颜色种类或增加限制条件。类似算法套路是通过合适的数据结构（如前缀和数组）优化对矩阵子区域的统计，利用单调性等性质采用双指针、二分等方法优化枚举过程。

### 相似知识点洛谷题目
- **P1387 最大正方形**：同样涉及矩阵，需通过动态规划和前缀和思想，在给定矩阵中找到满足条件的最大正方形。
- **P2701 硬币游戏**：利用二维前缀和优化对矩阵子区域的计算，结合题目规则解决问题。
- **P1719 最大加权矩形**：通过预处理前缀和，在加权矩阵中寻找最大加权矩形，与本题优化思路类似。

### 个人心得摘录与总结
无

---
处理用时：113.16秒