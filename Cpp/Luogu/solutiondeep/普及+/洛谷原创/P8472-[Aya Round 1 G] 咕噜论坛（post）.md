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

• 综合分析与结论：这些题解思路大致相同，均先利用二维前缀和预处理三种颜色的数量，以优化子矩阵内颜色数量的查询为O(1)时间复杂度。因暴力枚举子矩阵四个顶点的O(n^2m^2)复杂度过高，故通过枚举子矩阵的上下两行（或左右两列），结合双指针确定左右（或上下）边界，将时间复杂度降至O(n^3) 。同时都注意到要特判全紫名矩阵的情况。
    - 思路清晰度：多数题解都清晰阐述思路，但部分题解在细节处理上的解释不够详尽。
    - 代码可读性：部分题解代码注释详细，结构清晰，但有些题解变量命名不够直观，影响可读性。
    - 优化程度：都采用了二维前缀和与双指针优化，优化程度相当。

所选的题解：
  - 作者：chen_zhe (赞：14)  星级：4星
    - 关键亮点：思路清晰，先介绍预处理二维前缀和，再阐述通过枚举子矩阵的第一行和最后一行，利用二维前缀和差分判断能否用神权使子矩阵颜色相同，并用双指针计算最大整齐度，最后说明输出方案的实现方式，对corner cases也有提及。
    - 个人心得：无
    - 核心代码片段：
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
    // 后续为输出部分代码，省略
    return 0;
}
```
核心实现思想：`check1`函数通过二维前缀和判断子矩阵能否通过神权操作变为同色（非紫色），`check2`函数判断子矩阵是否全为紫色。主函数中先预处理前缀和，然后通过双指针枚举子矩阵的上下边界和左右边界，更新最大整齐度及对应子矩阵的位置。

  - 作者：KingPowers (赞：8)  星级：4星
    - 关键亮点：先分析暴力做法的复杂度，再提出优化思路，即通过只枚举子矩阵的上下两行并用双指针处理左右边界来降低复杂度，逻辑清晰，代码注释详细，对判断子矩阵能否变为某种颜色的函数有清晰定义。
    - 个人心得：无
    - 核心代码片段：
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
    // 后续为全变灰、全紫及输出部分代码，省略
    return 0;
}
```
核心实现思想：定义`check_B`、`check_G`、`check_P`函数分别判断子矩阵能否变为全棕、全灰、全紫。主函数中先预处理前缀和，然后分别枚举上下边界，通过双指针移动右边界，判断并更新最大同色子矩阵。

  - 作者：chenzefan (赞：3)  星级：4星
    - 关键亮点：先说明暴力解法的复杂度及不可行性，引出二维前缀和与双指针的优化方法，将问题分成棕名、灰名和紫名三类判断，代码注释详细，对每种颜色的处理过程清晰展示。
    - 个人心得：无
    - 核心代码片段：
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
    // 后续为考虑灰色、紫色及输出部分代码，省略
    return 0;
}
```
核心实现思想：`check`函数通过前缀和判断子矩阵能否变为指定颜色。主函数中先预处理前缀和，然后针对每种颜色枚举上下边界，利用双指针确定左右边界，更新最大同色子矩阵的大小、范围及颜色。

最优关键思路或技巧：利用二维前缀和优化子矩阵内颜色数量的查询，通过枚举子矩阵的部分边界（如上下行）结合双指针确定其余边界，从而降低时间复杂度。同时在判断子矩阵能否变为同色时，充分考虑紫名不可修改的特性进行条件判断。

可拓展之处：同类型题常涉及矩阵相关的最值问题，类似算法套路是遇到矩阵元素统计或最值求解时，若暴力枚举复杂度高，可考虑利用前缀和优化查询，通过合理减少枚举维度并结合双指针等方法降低复杂度。

推荐题目：
  - P1387 最大正方形：给定01矩阵，求全为1的最大正方形面积，可通过动态规划及类似前缀和思想求解。
  - P4147 玉蟾宫：在一个有障碍的矩阵中找最大全为F的子矩阵，同样可利用前缀和与单调栈等优化求解。
  - P2701 硬币游戏：在矩形区域内放置硬币，涉及矩阵覆盖问题，可借鉴本题减少枚举维度的思路。

个人心得摘录与总结：无。 

---
处理用时：106.94秒