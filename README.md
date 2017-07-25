# inihpp


Make ini file more easy.

Only need to include the "inihpp.h" to your proj, and enjoy it.


## Read

```
inihpp ini;
ini.parse(file);
ini.get("database", "comment");
```

## Write

```
inihpp ini;
ini.set("history", "mem_port", "8964");
ini.save("main.ini");
```
