# 题目信息

# [CCC 2008 J3] GPS Text Entry

## 题目描述

For her birthday, Sandy got a Global Positioning System (GPS) unit, which is an electronic device she can use to track the local hiking trails. Along the way Sandy can mark waypoints that can be recorded on a map when she gets home. A description of each waypoint can be entered in the unit, however the device does not have a keypad. Instead it has four cursor buttons, up, down, left, and right, and a button to accept the letter. The keypad looks like the following:

![](https://cdn.luogu.com.cn/upload/image_hosting/cqgjhd0p.png)

The screen displays a grid of the letters and symbols that can be used to “type out” the description. Here is the layout of the grid:

![](https://cdn.luogu.com.cn/upload/image_hosting/btdfon2b.png)

When you enter the name of the waypoint, the cursor starts at the `A`. You must move the cursor to the location of the next letter or symbol and then accept that letter. The cursor can only move to squares which are adjacent horizontally or vertically (not diagonally). Once you have entered all the letters in the description, you need to move the cursor to `enter` and accept the entire phrase.

You are to write a program that will calculate the number of cursor movements it takes to “type in” a phrase. For example, to enter the word `GPS`, starting from the `A` position, you would move down $1$ to select `G`, then move right $3$ and down $1$ to select `P`, then move down 1 and left $3$ to select `S` and finally move down $1$ and right $5$ to select `enter`. This is a total of $15$ cursor movements. Note that the total number of cursor movements does not change if you choose to move down and then across or across and then down. Also note that you cannot move beyond the boundaries of the grid (e.g., you cannot move off the grid nor `wrap-around` the grid).

## 说明/提示

数据保证合法。

## 样例 #1

### 输入

```
GPS```

### 输出

```
15```

## 样例 #2

### 输入

```
ECHO ROCK```

### 输出

```
29```

# AI分析结果

### 算法分类
模拟

### 综合分析
本题的核心是通过模拟光标在键盘上的移动来计算输入一个短语所需的总移动步数。所有题解都采用了类似的思路：首先初始化键盘布局，然后计算每个字符之间的曼哈顿距离，最后累加所有移动步数。不同题解在实现细节上有所差异，但整体思路一致。

### 所选题解
1. **作者：MarsTraveller (赞：6)**
   - **星级：5**
   - **关键亮点：**
     - 使用两个`map`存储字符的位置，代码清晰易读。
     - 详细解释了每一步的实现思路，特别是初始化键盘布局和计算距离的部分。
     - 代码结构清晰，注释详细，便于理解。
   - **核心代码：**
     ```cpp
     void keyboard() {
         for(char i = 'A';i <= 'Z';i++) {
             x[i] = 1+(i-'A')/6;
             y[i] = (i-'A')%6+1;
         }
         x[' '] = x['-'] = x['.'] = 5;
         y[' '] = 3, y['-'] = 4, y['.'] = 5;
     }
     big dis(big x,big y) {
         return abs(x-pntx)+abs(y-pnty);
     }
     int main() {
         keyboard();
         getline(cin,s);
         for(big i = 0;i < s.length();i++) {
             ans += dis(x[s[i]],y[s[i]]);
             pntx = x[s[i]], pnty = y[s[i]];
         }
         ans += dis(5,6);
         cout << ans;
         return 0;
     }
     ```

2. **作者：UniGravity (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 使用了简单的坐标计算方法，代码简洁。
     - 通过`id`变量统一处理字符到坐标的映射，减少了代码冗余。
     - 代码逻辑清晰，易于理解。
   - **核心代码：**
     ```cpp
     signed main() {
         getline(cin, s);
         int lstx = 0, lsty = 0, x, y, id;
         int ans = 0;
         s += '\n';
         for (int i = 0; i < s.length(); i++) {
             if (s[i] == ' ') id = 26;
             else if (s[i] == '-') id = 27;
             else if (s[i] == '.') id = 28;
             else if (s[i] == '\n') id = 29;
             else id = s[i] - 'A';
             x = id % 6;
             y = id / 6;
             ans += abs(x - lstx) + abs(y - lsty);
             lstx = x;
             lsty = y;
         }
         cout << ans;
         return 0;
     }
     ```

3. **作者：__O_v_O__ (赞：0)**
   - **星级：4**
   - **关键亮点：**
     - 使用两个数组分别存储字符的`x`和`y`坐标，代码简洁。
     - 通过`t`变量统一处理字符到坐标的映射，减少了代码冗余。
     - 代码逻辑清晰，易于理解。
   - **核心代码：**
     ```cpp
     signed main() {
         ios::sync_with_stdio(0);
         getline(cin,a);
         afor(i,0,a.size()-1,STB) {
             int t=0;
             if(a[i]>='A'&&a[i]<='Z')t=a[i]-'A';
             else if(a[i]==' ')t=26;
             else if(a[i]=='-')t=27;
             else t=28;
             ans+=(abs(x[t]-nx)+abs(y[t]-ny));
             nx=x[t],ny=y[t];
         }
         cout<<ans+abs(x[29]-nx)+abs(y[29]-ny);
         return 0;
     }
     ```

### 最优关键思路
- **曼哈顿距离计算**：通过计算两个字符之间的曼哈顿距离（横纵坐标差的绝对值之和）来确定光标移动的步数。
- **字符到坐标的映射**：通过统一的映射方法（如`id`或`t`变量）将字符映射到其对应的坐标，减少了代码冗余。
- **初始化键盘布局**：通过初始化函数或数组来存储键盘布局，便于后续计算。

### 可拓展之处
- **类似问题**：可以扩展到其他需要模拟光标移动的问题，如模拟键盘输入、模拟鼠标点击等。
- **优化思路**：可以考虑使用更高效的数据结构来存储键盘布局，如哈希表，以提高查找效率。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：34.97秒