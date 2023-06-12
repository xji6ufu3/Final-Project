Final Project      Program Design (II)

Team:福音戰士

Teacher:程芙茵 教授 Member:411410009林薇琪 411410025謝侑汧 411410041許庭翊 411410049陳芊綺 411410071鄭婷云 411410072楊家昕

**Introduction**

In this program you open a restaurant. You are a waiter, chief and also deliver.First, you are a waiter who inputs customer's orders into a txt. Then, you are a chef who cooks food with a keyboard. After that, you are a delivery person who delivers customer's orders to their house.

**Ordering System:**

1. Launch front.exe using the command prompt (cmd).

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.001.png)

2. If recording.txt and number.txt have not been cleared from previous orders, you will be prompted to either clear them or exit the program. If you choose not to clear them, the existing orders will be continued.

recording.txt stores order details, while number.txt stores the order number from the last order.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.002.png)

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.003.png)

3. Enter the desired operation.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.004.png)

There are a total of seven operations to choose from:

1. help: Displays the descriptions of these seven operations.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.005.png)

2. order: Enters the ordering system and allows you to enter meal codes.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.006.png)

Suppose a customer wants to order meals with codes a, b, and c. You would enter abc.

After entering the codes, the order details will be displayed, including the order number, meal code, meal name, and order price.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.007.png)

Except for the meal code, all other details will be saved in recording.txt.

If a non-lowercase English word or 0 is entered, an error message will be displayed, and you will be asked to re-enter.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.008.png)

Entering 0 will end the order function and return to the command prompt.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.009.png)

3. delete: Enter the order number to delete a specific order. If the deletion is successful, the delete operation will exit.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.010.png)

Entering an incorrect number will prompt you to re-enter it, and entering 0 will exit the delete function.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.011.png)

4. traverse: Displays all order details in a specific format: order number, meal code, meal name, and order price.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.012.png)

5. search: Enter a specific order number to display the details of that order on the screen and exit the search operation.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.013.png)

If an incorrect number is entered, a warning message will be displayed, and you will be asked to re-enter.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.014.png)

If the entered order number does not exist, a warning message will be displayed, and you will be asked to re-enter.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.015.png)

To exit the search operation, enter 0.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.016.png)

6. sort: Enter the data type by which you want to sort the orders.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.017.png)

To sort by order number, enter "number".

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.018.png)

Using the traverse operation, you can see the order in sorted order.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.019.png)

To sort by order price, enter "price".

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.020.png)

Using the traverse operation, you can see the order in sorted order.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.021.png)

To exit the sort operation, enter "exit".

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.022.png)

7. exit: Ends front.exe.![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.023.jpeg)

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.024.png)

It will also automatically launch the cooking and delivery game type\_and\_maze.exe.

**Type and Maze Game:**

1. It will ask you whether you want to play the game in hard mode(the default level is easy mode)(the answer can type either in upper or lower case)

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.025.png)

1. easy mode:

The alphabets you input can be either upper or lower case, it does not influence how we judge.

2. hard mode:

The alphabets you input should precisely match the instructions on the screen. And the alphabet for the ingredient you need to type would switch to upper or lower case randomly.

2. After choosing the level, it will show what dish you are going to cook now.You need to type all the ingredients in demanding time, after it counts down “3 2 1 start”.![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.026.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.027.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.028.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.029.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.030.jpeg)
2. You will get three results depending on your performance.
1. If you type the ingredients correctly and also in the limited time, you can earn this dish's price.
1. If you type the wrong ingredients, it means you didn't cook the correct dish. And the dish should be thrown in the trash can, you can't sell this dish and also you can't get the money.(use delete function to delete the dish form order)
1. If you type too slowly, that has already exceeded the demanding time, the dish will burn. You can't sell this dish and also you can't get the money.(use delete function to delete the dish form order)
4. When you finish the type game, you can play the maze game, and the map will be displayed on the screen.



|‘@’|‘ ‘(SPACE)|‘#’|‘$’|‘\*’|
| - | - | - | - | - |
|terminal point|road|wall|chance card|player|

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.031.png)

5. After a 3 seconds countdown, the game is about to start, and you have 30 seconds to reach the terminal point.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.032.png)

6. You can use the ↑←↓→(arrow keys) to play the maze game.
6. If you eat the '$'(chance card), you will have 3 possible outcomes.
1. You picked up 10 dollars.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.033.png)

2. The order failed because you were chased by a dog.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.034.png)

3. You coincidentally met the customer on the way, so the order is completed.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.035.png)

8. If you reach the end point in 30 seconds, the income of this order will add 10%, and it will not matter if you don’t reach the terminal point, because the maze game is just a bonus.

**History Record:**

1. It is a File which includes functions that work in ‘type and maze game’, ‘ordering system’, and the ending printf file. The file’s main function is to record player’s historical records and read the file to initialize some variables.
1. Introducing functions:
1. int num\_func():The function reads ‘counting.txt’, counts the lines that exist in the file then returns the value. The value stores how many times the player had played the game, which will be used to print the history records.
1. int record(float a, int b, char word[10]):I use strftime（); to record the time that player ends the game. And record the total money and the dishes the player has made so that when the system reads the file next time, the player can continue the previous records.
1. int history\_show(int num):The function will show the history records for the player to choose which record the player wants to continue with.The fseek（); in the function is to find the end of the file because it only needs to output the latest ten data, and continue to find the previous data according to the number of digits deducted forward.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.036.jpeg)

4. int restart(int num):The function will ask players whether or not they want to continue with their historical records. If the player chooses to continue the game, then it will call the his\_search（); function to read previous data.
4. int his\_search(int choice, int num）:The function reads the file which records the previous data of total money and total dishes, save it to another file’history.txt’.
4. values earn\_initialization():The function will read the file ‘history.txt’to bring out the data of total money and dishes, then send them to the main system to initialize the money and dish to the previous data.

**Program Design:**

**Basic Part:![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.037.jpeg)**

1. Data Type and Data Structure

The structure used to store orders consists of three different basic data types: int, double, char.

The char array meal[] is of string type and utilizes Flexible Array Members to save space. The storage of orders is implemented using a doubly linked list.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.038.png)

2. Operations
1. add: In front.exe, the order operation is used to add new orders.
1. delete:
1. In front.exe, the delete operation is used to remove a specific order by its number.
2. In type\_amd\_maze.exe, the delete operation is used to remove the dish that you failed to cook(typed wrong ingredient or exceeded demand time) from that order automatically.![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.039.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.040.jpeg)
3. traverse: In front.exe, the traverse operation is used to list all orders in recording.txt. The output format is as follows: order number, meal name, order price. Each order is separated by a dashed line.
4. search: In front.exe, the search operation is used to find and display the details of a specific order by its number on the screen.![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.041.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.042.jpeg)
4. sort: In front.exe, the sort operation is used to sort all orders by number or price.
6. file io: Read from and write to recording.txt, number.txt, order.txt, after\_game.txt.![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.043.jpeg)![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.044.jpeg)

**Advanced Part**

1. Sort the doubly linked list
1. We have added game music and are using the built-in Windows library PlaySound for playback. However, we encountered a limitation with VSCode, as it cannot compile the code. Instead, we switched to using CodeBlocks. To overcome this limitation, we utilized the system function to open the executable file and play the music.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.045.png)

3. Use DFS to create random mazes
1. Added the path traveled to the doubly linked list

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.046.png)

2. Delete the way back

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.047.png)

3. Create the random map
1. We randomly choose a walk up, down, left, and right, and we record the path traveled,if we dead end.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.048.jpeg)

2. Create a chance card at the first dead end.

If you encounter a dead end, take a step back, and delete the road traveled.

If returned to the origin, the map is completed.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.049.jpeg)

4. The player uses the arrow keys to play the maze.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.050.png)

4. Typing master![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.051.jpeg)
1. convert\_letters
   1. If the player chooses to play in hard mode, we should convert the letter in the ingredient that the player needs to type.
   1. We convert them to upper or lower case randomly.
1. input and judge![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.052.jpeg)

After the player input the words. If he chooses to play in easy mode, we convert all the input into lower case.

Using clock() function to record how much time the player spent to input the words.

We judge whether he input the correct ingredients and he should also input in the limit time that we request.

5. UI
1. Expected Results:

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.053.jpeg)

2. Pratical CODE：
1. Introducing the graphics.h graphics-related library from easyx.h.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.054.png)

2. Declare a PNG and use the "loadimage" function to import the delivery man, door, and coin icons when printing the original map in the main function. Set the size to be equal to 1 \* 1 wall length unit.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.055.png)

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.056.jpeg)

3. Double Buffering (to avoid screen flickering on each loop):

Before entering the maze loop, use "BeginBatchDraw()": Preparing for drawing in memory first.

After drawing the maze, use "FlushBatchDraw()".

And after the loop ends, use "EndBatchDraw()": Output the completed drawing from memory.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.057.jpeg)

4. Drawing Functions:

setbkcolor: Set the background color of the pop-up window. cleardevice: Clear the window using the current color.

For example, if the current cell is a WALL, it will output a "white border, RGB(93,107,153) fill, filled inside the wall cell."

If the current cell is a PLAYER, it will output the previously imported "deliveryman.png" image.

The same applies to CHANCE (opportunity) and DOOR (exit) cells.

![](https://github.com/xji6ufu3/Final-Project/blob/main/Picture/Aspose.Words.f499ea7b-8fe5-4451-bd0f-212da94cf7d5.058.jpeg)

3. The regrettable aspect

One regrettable aspect is the incompatibility between my MAC OS system and the easyx graphics library. Although my team members' WINDOWS systems were able to access the easyx.h and graphics.h files, they encountered difficulties running the functions. Therefore, we reluctantly had to give up on this Advanced Part.

**Github Link**

https://github.com/xji6ufu3/Final-Project
