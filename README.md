# Simple but convenient log generator

This is a simple html log generator. See *examples* below to better understand how it works or [*documentation*](https://tralf-strues.github.io/log_generator/) where you can find out what each function does.

## Example 1 (Hello World)

```c++
#include "log_generator.h"

int main()
{
    LG_Init(); // initializes log file
    
    LG_Write("Hello, World!");
    
    LG_Close(); // closes log file
    
    return 0;
}
```

This code will produce the following log.html file:

```html
<!DOCTYPE html>
<html>
<head><link rel="stylesheet" href="log.css"></head>
<body>
Hello, World!
</body>
</html>
```

*How log.css could be used you can find in example 3.*

## Example 2 (Adding color)

```c++
#include "log_generator.h"

enum Error
{
	NO_ERROR,
	ERROR_CODE_1,
	ERROR_CODE_2,
	ERROR_CODE_3,
	ERROR_CODE_4
};

int main()
{
	Error status = NO_ERROR;
	
	/* ... something bad happened */
	status = ERROR_CODE_2;
	
	if (status != NO_ERROR)
	{
		LG_Init(); 
    
		// starts an error message with red color
		LG_WriteMessageStart(LG_COLOR_RED);
		
		LG_Write("An ERROR occured!\n");
		
		// works similar to printf(...)
		LG_Write("Error code is %d\n", status); 
		
		// ends the error message
		LG_WriteMessageEnd();
		
		LG_Close(); 
    }
	
    return 0;
}
```

This code will produce the following log.html file:

```html
<!DOCTYPE html>
<html>
<head><link rel="stylesheet" href="log.css"></head>
<body>

<pre style="color: rgb(255, 0, 0);">
An ERROR occured!
Error code is 2

</pre>

</body>
</html>
```

## Example 3 (Adding CSS classes)

You can also use CSS classes. The default log.css file can be found [here](https://github.com/tralf-strues/log_generator/blob/master/res/log.css). You can edit it and add your own classes to your liking, or change the default values if you wish.

```c++
#include "log_generator.h"

enum Error
{
	NO_ERROR,
	ERROR_CODE_1,
	ERROR_CODE_2,
	ERROR_CODE_3,
	ERROR_CODE_4
};

int main()
{
	Error status = NO_ERROR;
	
	/* ... something bad happened */
	status = ERROR_CODE_2;
	
	if (status != NO_ERROR)
	{
		LG_Init(); 
    
		// starts an error message with error style class
		LG_WriteMessageStart(LG_STYLE_CLASS_ERROR);
		
		LG_Write("An ERROR occured!\n");
		LG_Write("Error code is %d\n", status); 
		
		LG_WriteMessageEnd();
		
		LG_Close(); 
    }
	
    return 0;
}
```

This code will produce the following log.html file:

```html
<!DOCTYPE html>
<html>
<head><link rel="stylesheet" href="log.css"></head>
<body>

<pre class="LG_ERROR">
An ERROR occured!
Error code is 2

</pre>

</body>
</html>
```



