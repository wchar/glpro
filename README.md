## glpro -- a simple particle system module

* lua config base
* auto refresh
* great extension


### fire effect sample


	emittor
	{
	    count = 100,
	    speed = 30,
	    duration = 3,
	    
	    mod = {
	        scaleOverLife{ 
	            began = range(0.5, 1),
	            ended = range(2, 4),
	        },
	
	        alphaOverLife{
	            began = 0.6,
	            ended = 0.01,
	        },
	
	        colorOverLife{
	            began = range({0.8, 0.1, 0.1}, {1, 0.2, 0.1}),
	            ended = {0, 0, 0},
	        },
	
	        velOverLife{
	            began = range({-1, -1, -1}, {1, 1, 1}),
	            ended = range({-2, 4, -2}, {2, 6, 2}),
	        },
	    }
	}

![p1](https://github.com/wchar/glpro/blob/master/photos/fire.png)


### colorful effect sample

	emittor
	{
	    count = 100,
	    speed = 100,
	    duration = 1,
	
	    mod = {
	        scaleOverLife{ 
	            began = range(0.5, 1),
	            ended = 0.001,
	        },
	
	        alphaOverLife{
	            began = 2,
	            ended = 1,
	        },
	
	        initColor{
	            color = {1.5, 1.5 , 1.5},
	        },
	
	        colorOverLife{
	            began = range({0.2, 0.2, 0.2}, {1, 1, 1}),
	            ended = range({0.2, 0.2, 0.2}, {1, 1, 1}),
	        },
	
	        posOverLife{
	            began = {0 ,0, 0},
	            ended = range({-3, -2, -2}, {2, 2, 2}),
	        },
	
	        velOverLife{
	            began = range({-2, -2, -2}, {2, 2, 2}),
	            ended = range({-2, -2, -2}, {2, 5, 2}),
	        },
	    }
	}

![p2](https://github.com/wchar/glpro/blob/master/photos/colorful.png)


### mult emittor supposted
![p3](https://github.com/wchar/glpro/blob/master/photos/mult.png)
