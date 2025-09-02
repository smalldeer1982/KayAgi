# 题目信息

# Ingenuity-2

## 题目描述

Let's imagine the surface of Mars as an infinite coordinate plane. Initially, the rover Perseverance-2 and the helicopter Ingenuity-2 are located at the point with coordinates $ (0, 0) $ . A set of instructions $ s $ consisting of $ n $ instructions of the following types was specially developed for them:

- N: move one meter north (from point $ (x, y) $ to $ (x, y + 1) $ );
- S: move one meter south (from point $ (x, y) $ to $ (x, y - 1) $ );
- E: move one meter east (from point $ (x, y) $ to $ (x + 1, y) $ );
- W: move one meter west (from point $ (x, y) $ to $ (x - 1, y) $ ).

Each instruction must be executed either by the rover or by the helicopter. Moreover, each device must execute at least one instruction. Your task is to distribute the instructions in such a way that after executing all $ n $ instructions, the helicopter and the rover end up at the same point, or determine that this is impossible.

## 说明/提示

Let's consider the first example: the string $ S = \texttt{NENSNE} $ . One of the possible solutions, shown in the figure below, is $ p = \texttt{RRHRRH} $ , using which both the rover and the helicopter will end up one meter north and one meter east.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974D/6e8d0f788b954d2ceff54878d55afda06efd52c8.png)For WWW, the solution is impossible.

## 样例 #1

### 输入

```
10
6
NENSNE
3
WWW
6
NESSWS
2
SN
2
WE
4
SSNN
4
WESN
2
SS
4
EWNN
4
WEWE```

### 输出

```
RRHRRH
NO
HRRHRH
NO
NO
RHRH
RRHH
RH
RRRH
RRHH```

# AI分析结果

### 题目中文重写
# Ingenuity - 2

## 题目描述
让我们把火星表面想象成一个无限的坐标平面。最初，毅力号火星车 2 号（Perseverance - 2）和机智号直升机 2 号（Ingenuity - 2）位于坐标为 $(0, 0)$ 的点。为它们专门开发了一组由 $n$ 条以下类型指令组成的指令集 $s$：
- N：向北移动一米（从点 $(x, y)$ 移动到 $(x, y + 1)$）；
- S：向南移动一米（从点 $(x, y)$ 移动到 $(x, y - 1)$）；
- E：向东移动一米（从点 $(x, y)$ 移动到 $(x + 1, y)$）；
- W：向西移动一米（从点 $(x, y)$ 移动到 $(x - 1, y)$）。

每条指令必须由火星车或直升机执行。此外，每个设备必须至少执行一条指令。你的任务是分配这些指令，使得在执行完所有 $n$ 条指令后，直升机和火星车最终位于同一点，或者确定这是不可能的。

## 说明/提示
让我们考虑第一个示例：字符串 $S = \texttt{NENSNE}$。下面图中展示的一种可能的解决方案是 $p = \texttt{RRHRRH}$，使用这个方案，火星车和直升机最终都会在向北一米和向东一米的位置。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974D/6e8d0f788b954d2ceff54878d55afda06efd52c8.png)对于 WWW，此问题无解。

## 样例 #1
### 输入
```
10
6
NENSNE
3
WWW
6
NESSWS
2
SN
2
WE
4
SSNN
4
WESN
2
SS
4
EWNN
4
WEWE
```

### 输出
```
RRHRRH
NO
HRRHRH
NO
NO
RHRH
RRHH
RH
RRRH
RRHH
```

### 综合分析与结论
这些题解的主要思路围绕如何合理分配指令，使得两个机器人最终到达同一位置，同时满足每个机器人至少执行一条指令的条件。
- **思路对比**：部分题解采用贪心策略，在每一步根据机器人的位置关系决定指令分配；部分题解先统计各方向指令数量，依据奇偶性判断是否有解，再进行指令分配。
- **算法要点**：统计各方向指令数量，判断奇偶性以确定是否有解；通过贪心、模拟等方法进行指令分配。
- **解决难点**：处理每个机器人至少执行一条指令的限制，避免出现某个机器人没有执行指令的情况；处理指令数量为奇数时的分配问题。

### 所选题解
- **作者：Weekoder (赞：7)，4星**
    - **关键亮点**：思路清晰，通过贪心策略，在每一步根据机器人的位置关系和是否执行过指令来分配指令，代码实现简洁易懂。
    - **个人心得**：无
- **作者：Eddie08012025 (赞：6)，4星**
    - **关键亮点**：先统计各方向指令数量，根据奇偶性判断是否有解，对特殊情况进行特判，逻辑严谨。
    - **个人心得**：无
- **作者：gu51yo (赞：5)，4星**
    - **关键亮点**：利用操作数的奇偶性实现指令分配，代码简洁，逻辑巧妙。
    - **个人心得**：无

### 重点代码
#### Weekoder 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, X1, Y1, X2, Y2;
string s, ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T --) {
        cin >> n >> s;
        s = '#' + s;
        ans = "";
        bool f1 = 0, f2 = 0;
        X1 = Y1 = X2 = Y2 = 0;
        for (int i = 1; i <= n; i++) {
            if (s[i] == 'N') {
                if (Y1 > Y2 || Y1 == Y2 && !f2)
                    Y2++, ans += 'H', f2 = 1;
                else
                    Y1++, ans += 'R', f1 = 1; 
            } 
            else if (s[i] == 'S') {
                if (Y1 > Y2 || Y1 == Y2 && !f1)
                    Y1--, ans += 'R', f1 = 1;
                else
                    Y2--, ans += 'H', f2 = 1; 
            } 
            else if (s[i] == 'E') {
                if (X1 > X2 || X1 == X2 && !f2)
                    X2++, ans += 'H', f2 = 1;
                else
                    X1++, ans += 'R', f1 = 1; 
            } 
            else {
                if (X1 > X2 || X1 == X2 && !f1)
                    X1--, ans += 'R', f1 = 1;
                else
                    X2--, ans += 'H', f2 = 1; 
            } 
        }
        if (X1 != X2 || Y1 != Y2 || !f1 || !f2)
            cout << "NO\n";
        else
            cout << ans << "\n"; 
    }
    return 0;
}
```
**核心实现思想**：遍历指令，根据机器人的位置关系和是否执行过指令来分配指令，最后判断两个机器人是否到达同一位置且都执行过指令。

#### Eddie08012025 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,z[200];//z数组存储NSEW的个数 
string a;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>a;
        z['N']=z['S']=z['E']=z['W']=0;//多组样例，初始化 
        for(int i=0;i<n;i++){//统计个数 
            z[a[i]]++;
        }
        if(z['N']==1&&z['S']==1&&z['E']==0&&z['W']==0||z['N']==0&&z['S']==0&&z['E']==1&&z['W']==1||z['N']%2!=z['S']%2||z['E']%2!=z['W']%2){
            cout<<"NO\n";
            continue;
        }
        if(z['N']==1&&z['S']==1&&z['E']==1&&z['W']==1){
            for(int i=0;i<n;i++){
                if(a[i]=='N'||a[i]=='S')cout<<'R';//NS给Rower 
                else cout<<'H';//WE给Helicopter 
            }cout<<"\n";
            continue;
        }
        z['N']/=2;
        z['S']/=2;
        z['E']/=2;
        z['W']/=2;
        for(int i=0;i<n;i++){//输出 
            if(z[a[i]]){
                cout<<"R";
                z[a[i]]--;
            }else{
                cout<<"H";
            }
        }cout<<"\n";
    }
    return 0;
}
```
**核心实现思想**：先统计各方向指令数量，根据奇偶性和特殊情况判断是否有解，若有解则将指令平均分配给两个机器人。

#### gu51yo 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x, y;
string s;
void solve () {
    cin >> n >> s;
    vector<int> a(n), b(5);
    for (int i=0; i<n; i++) {
        a[i]="NESW"s.find(s[i]);	//操作转换为整数
        b[a[i]]++;
    }
    x=b[1]-b[3], y=b[0]-b[2];
    if (x%2 || y%2 || (x==2 && y==2 && n<3)) {	//不可能
        cout << "NO\n";
        return;
    }
    for (int i=0; i<n; i++) {	//输出
        cout << "HR"[(a[i]+b[a[i]]++)%2];	//奇偶
    } cout << '\n';
}
int main () {
    cin >> t;
    while (t--) solve();
    return 0;
}
```
**核心实现思想**：将操作转换为整数，统计各方向指令数量，根据奇偶性判断是否有解，若有解则利用操作数的奇偶性实现指令分配。

### 最优关键思路或技巧
- **奇偶性判断**：通过统计各方向指令数量的奇偶性，快速判断是否有解。
- **贪心策略**：在每一步根据机器人的位置关系和是否执行过指令来分配指令，使两个机器人尽量靠近。

### 可拓展之处
同类型题可能会改变指令类型、增加机器人数量或限制条件等。类似算法套路包括贪心算法、模拟算法等，可根据具体问题灵活运用。

### 推荐洛谷题目
- P2689 东南西北
- P1006 传纸条
- P1007 独木桥

### 个人心得摘录与总结
- **__K2FeO4**：一开始采用相对运动的方法，认为目标状态是东西、南北对半分，但忽略了每个机器人至少执行一条指令的条件，导致部分测试用例错误。后来通过记录答案，遍历答案数组找到相对的指令并改变操作对象，解决了问题。总结：在解题时要仔细阅读题目条件，考虑全面，避免遗漏特殊情况。

---
处理用时：50.71秒