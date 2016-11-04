# stopLoL
StopLoL is a little program I made to prevent League of Legends from running when a number of games per day is reached.
This is a visual studio project, if you want to compile it, you will have to add _CRT_SECURE_NO_WARNING to your preprocessor options, here is a guide : http://stackoverflow.com/questions/16883037/remove-secure-warnings-crt-secure-no-warnings-from-projects-by-default-in-vis

# To-do list
-Improve the numGames() function since it depends on log files and it can be easely bypassed by deleting log files.
Here is more informations about games log files : https://support.riotgames.com/hc/fr/articles/201752674-Logs-r%C3%A9seau-syst%C3%A8me-et-League-of-Legends

-Do not use  "using namespace std;", I got lazy there but you should use the std:: prefix.

-Improve the way I handled strings and convertion ( converting wchar_t to strings so it's easier to manipulate).

-Add some kind of persistence to the program so it can't be terminated if you're trying to prevent your kid from playing LoL :-).

# Additional informations
-This program is license free and open-source, use it as you want but give me credits when you do by linking to this github repo ;).
-I will gladly recieve any criticism on my way of coding or any tips to help me improve.
