# Geek Party VJ
## about
This is a VJ app which draws:
* data (letters) in JSON from another apps (which is a node.js server for now)
* movie inputs from another apps (which is VDMX with syphon output for now)
and is purely audio-reactive. Sound data is being passed from anotehr apps like Max/MSP. The controller is [this one]().

Server side app is working on local-env to fetch tweet data and rewrite external JSON file.

See these demos.
* https://twitter.com/ayumu_naga/status/893173868550012928
* https://twitter.com/ayumu_naga/status/893517727595352065
* https://twitter.com/tks/status/893741817748795392

This was created for for [AkiParty 2017](http://akiparty2017.cs8.biz/).

## Dependency
* node v7.9.0
* openFrameworks
    * ofxOsc
    * ofxDeferredShading
    * ofxSyphon
    * ofxTrueTypeFontUC
    * ofxGui
    * ofxJSON
