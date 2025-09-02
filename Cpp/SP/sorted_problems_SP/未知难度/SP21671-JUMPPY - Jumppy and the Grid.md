---
title: "JUMPPY - Jumppy and the Grid"
layout: "post"
diff: 难度0
pid: SP21671
tag: []
---

# JUMPPY - Jumppy and the Grid

## 题目描述

```
<pre style="text-align: justify;"><p style="white-space: normal;"><span style="font-family: arial, helvetica, sans-serif;">Jumppy likes to jump! One day Jumppy went to a park. Jumppy can jump all over the park.The park can be thought of as a square grid with square cells of side length 1. The contents of the grid is either 0(zero) or X. There are certain things which Jumppy likes. They are:<br></br><br></br>->Jumppy likes rectangles.<br></br>->Jumppy likes X.<br></br><br></br>Therefore Jumppy will jump only in the rectangles consisting of X. A rectangle is defined as follows:<br></br><br></br>1)The whole rectangular region should contain only X.<br></br>2)The rectangle should be surrounded with 0 or the boundary of the grid.<br></br>3)The diagonally adjacent cell(see the definition) of the corner of the rectangle may be X or 0.(Refer to the first example).<br></br><br></br>Diagonally adjacent cell: Suppose the given cell has coordinates (p,q) then its diagonally adjacent cells would have coordinates (p+1,q+1) , (p+1,q-1) , (p-1,q+1) , (p-1,q-1).<br></br><br></br>Now Jumppy is curious how many rectangles are there in the park. Help Jumppy find the number of rectangle.</span></p><p style="white-space: normal;"><span style="font-family: arial, helvetica, sans-serif;"><strong>INPUT:</strong><br></br>An integer n denoting the side of the grid.<br></br>Then n lines follow each containing a string of n characters describing the square grid. All the characters will be either 0 or X.<br></br><br></br><strong>OUTPUT:</strong><br></br>Output the number of rectangles in the given grid.<br></br><br></br><strong>CONSTRAINTS:</strong><br></br>0 < n <= 1000</span></p><p style="white-space: normal;"><strong><span style="font-family: arial, helvetica, sans-serif;">EXAMPLES:</span></strong></p><p style="white-space: normal;"><span style="font-family: arial, helvetica, sans-serif;"><br></br><strong>INPUT:</strong><br></br>4<br></br>XX00<br></br>XX00<br></br>00XX<br></br>00XX<br></br><br></br><strong>OUTPUT: </strong><br></br>2<br></br><br></br>INPUT:<br></br>5<br></br>00000<br></br>0XXX0<br></br>0XXX0<br></br>0XXX0<br></br>00X00<br></br><br></br><strong>OUTPUT:</strong> <br></br>0<br></br><br></br><strong>INPUT:</strong><br></br>5<br></br>00000<br></br>0XXX0<br></br>0X0X0<br></br>0XXX0<br></br>00000<br></br><br></br><strong>OUTPUT:</strong><br></br>0<br></br><br></br><strong>INPUT:</strong><br></br>3<br></br>X0X<br></br>0X0<br></br>X0X<br></br><br></br><strong>OUTPUT: </strong><br></br>5<br></br><br></br><strong>EXPLANATION: </strong><br></br>Case 1: As can be seen there are two rectangles as highlighted.<br></br>Case 2: The grid contains no rectangles because it violets the second condition of definition.<br></br>Case 3: The grid contains no rectangles because it violets the first condition of definition.<br></br>Case 4: The individual X in this case can be considered as rectangles.</span></p>
```

