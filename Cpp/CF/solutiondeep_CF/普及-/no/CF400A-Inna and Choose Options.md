# 题目信息

# Inna and Choose Options

## 题目描述

Inna 在玩井字棋的升级版。游戏规则如下：

在游戏开始前，他将 $12$ 张卡片排列在桌子上。每张卡片上都有一个字符 `X` 或 `O`。然后玩家选择两个正整数 $a$ 和 $b$ $(a\times b=12)$ 
，然后根据放在桌子上的卡片制作一个 $a\times b$ 大小的表格，前 $b$ 
 张卡片组成第一行，接下来的 $b$ 张卡片组成第二行，依此类推，最后的 $b$ 张卡片组成最后一行（第 $a$ 行）。玩家获胜的条件是表格中某一列的所有卡片都含有字符 `X`。否则，玩家失败。

Inna 已经把 $12$ 张卡片按顺序放在了桌子上。但不幸的是，她不知道选择什么样的 $a$ 和 $b$ 来帮助她赢得游戏，所以她让你输出可能的所有选择 $a,b$，以及能够获胜的方式。

## 样例 #1

### 输入

```
4
OXXXOXOOXOOX
OXOXOXOXOXOX
XXXXXXXXXXXX
OOOOOOOOOOOO
```

### 输出

```
3 1x12 2x6 4x3
4 1x12 2x6 3x4 6x2
6 1x12 2x6 3x4 4x3 6x2 12x1
0
```

# AI分析结果

### 题目内容
Inna 在玩井字棋的升级版。游戏规则如下：

在游戏开始前，他将12张卡片排列在桌子上。每张卡片上都有一个字符`X`或`O`。然后玩家选择两个正整数`a`和`b` (`a×b = 12`) ，然后根据放在桌子上的卡片制作一个`a×b`大小的表格，前`b` 张卡片组成第一行，接下来的`b`张卡片组成第二行，依此类推，最后的`b`张卡片组成最后一行（第`a`行）。玩家获胜的条件是表格中某一列的所有卡片都含有字符`X`。否则，玩家失败。

Inna 已经把12张卡片按顺序放在了桌子上。但不幸的是，她不知道选择什么样的`a`和`b`来帮助她赢得游戏，所以她让你输出可能的所有选择`a,b`，以及能够获胜的方式。

### 样例 #1
#### 输入
```
4
OXXXOXOOXOOX
OXOXOXOXOXOX
XXXXXXXXXXXX
OOOOOOOOOOOO
```
#### 输出
```
3 1x12 2x6 4x3
4 1x12 2x6 3x4 6x2
6 1x12 2x6 3x4 4x3 6x2 12x1
0
```
### 算法分类
模拟
### 题解综合分析与结论
所有题解都基于模拟的思路，利用12的因数组合有限（仅6种：1×12、2×6、3×4、4×3、6×2、12×1）这一特性，对每种组合构造矩阵并判断是否存在全为`X`的列。不同题解在代码实现上略有差异，如判断全`X`列的方式、存储结果的方式等，但核心思路一致。

### 所选的题解
- **作者：shiziyu111（5星）**
    - **关键亮点**：思路清晰，代码简洁明了。通过数组存储12的因数，利用多层循环枚举每种矩阵情况及每列元素，判断是否满足获胜条件，最后统一输出结果。
    - **重点代码核心实现思想**：外层循环遍历12的因数组合，内层循环判断每列是否全为`X`，若满足则记录该组合。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        char s[13];
        int b[6]={1,2,3,4,6,12};//具体方案
        int ans[7]={0},cnt=0;
        for(int i=1;i<=12;i++)
        {
            cin>>s[i];
        }
        for(int i=0;i<6;i++)
        {
            int flagg=0;//记录此方案是否成立
            for(int k=1;k<=b[i];k++)
            {
                if(flagg==1)
                {
                    continue;
                }
                int flag=1;
                for(int j=k;j<=12;j+=b[i])
                {
                    if(s[j]=='O')
                    {
                        flag=0;
                    }
                }
                if(flag==1)
                {
                    cnt++;
                    ans[cnt]=b[i];
                    flagg=1;
                }
            }   
        }
        cout<<cnt<<" ";
        for(int i=cnt;i>=1;i--)
        {
            cout<<12/ans[i]<<"x"<<ans[i]<<" ";//用正序存的b，但是要正序输出a，所以要逆序输出
        }
        cout<<endl;
    }
    
    return 0;
}
```
- **作者：xuchuhan（4星）**
    - **关键亮点**：代码结构清晰，先枚举所有合法的`a,b`组合，将字符串转化为字符矩阵后判断矩阵是否合法，符合模拟题的常规解题思路，且对矩阵转化过程有清晰的代码实现。
    - **重点代码核心实现思想**：通过两层循环将字符串按`a,b`组合转化为矩阵，再通过两层循环判断矩阵每列是否全为`X`，若满足则记录结果。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,ans;
char a[20];
int y12[15]={0,1,2,3,4,6,12};
char c[15][15];
int p[15];
signed main(){
    cin>>t;
    while(t--){
        for(int i=1;i<=12;i++)
            cin>>a[i];
        for(int i=1;i<=6;i++){
            int x=y12[i];
            int y=12/y12[i];
            //合法的两条边
            for(int j=1;j<=12;j++){
                int h=j/y+(j%y!=0);
                int l=j%y+y*(j%y==0);
                c[h][l]=a[j];
            }
            //转化矩阵
            bool flag=0;
            for(int j=1;j<=y;j++){
                bool f=0;
                for(int i=1;i<=x;i++){
                    if(c[i][j]!='X')
                        f=1;
                }
                if(!f)
                    flag=1;
            }
            if(flag){
                ans++;
                p[ans]=x;
            }
            //如果合法就存储
        }
        cout<<ans<<" ";
        for(int i=1;i<=ans;i++)
            cout<<p[i]<<"x"<<12/p[i]<<" ";
        cout<<"\n";
        //统一输出
        ans=0;
    }
    return 0;
}
```
- **作者：OIerWu_829（4星）**
    - **关键亮点**：利用二维数组存储矩阵，代码逻辑清晰易懂，通过两层循环填充矩阵，再通过两层循环判断每列是否满足条件，符合常规模拟题的解题方式。
    - **重点代码核心实现思想**：先通过两层循环将字符串按不同`a,b`组合存入二维数组，再通过两层循环判断每列是否全为`X`，若满足则记录该方案。
```cpp
#include <iostream>
using namespace std;
char a[20][20];
int ans1[10], ans2[10];
const int x[] = {1, 2, 3, 4, 6, 12};
const int y[] = {12, 6, 4, 3, 2, 1};
int main()
{
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int cnt = 0;
        for (int k = 0; k < 6; k++) {
            int n = x[k], m = y[k], id = 0;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++)
                    a[i][j] = s[id++]; // 存储字符串 s 的每一个字符
            for (int i = 1; i <= m; i++) {
                bool flag = true;
                for (int j = 1; j <= n; j++)
                    if (a[j][i] == 'O') flag = false;
                if (flag) { ans1[++cnt] = n; ans2[cnt] = m; break; } // 可行，存储起来
            }
        }
        cout << cnt << " \n"[cnt == 0]; // 如果方案数为 0 则直接换行
        for (int i = 1; i <= cnt; i++)
            cout << ans1[i] << "x" << ans2[i] << " \n"[i == cnt];
    }
    return 0;
}
```
### 最优关键思路或技巧
利用12的因数组合有限这一特点，直接枚举所有可能的矩阵组合，通过循环判断每列是否全为`X`，这种直接模拟的方法简单有效。在代码实现上，合理利用数组存储因数和结果，能使代码逻辑更清晰。

### 可拓展之处
同类型题通常会改变数据规模或判断条件。例如改变卡片数量，此时若因数组合仍较少可继续使用模拟；若因数组合过多，可能需优化算法，如利用更高效的数据结构存储矩阵，或优化判断全`X`列的方法。类似算法套路是对于条件明确、数据规模小的问题，可直接枚举所有可能情况进行模拟判断。

### 洛谷相似题目推荐
- [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)

---
处理用时：82.38秒