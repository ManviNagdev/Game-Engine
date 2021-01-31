## Game Engine Development in C++

In this project, I built a game engine in C++ from scratch. It allows multiple players to play the game synchronously and works well for 2D platformers. It follows object-oriented design and makes extensive use of inheritance, encapsulation, abstraction, and polymorphism. Other key concepts that were used are from client-server communication, event handling, logical time, multithreading, physics, and socket programmning.

### Libraries Used
1. SFML (Simple and Fast Multimedia Library): For providing simple application programming interface to various multimedia components. [Download](https://www.sfml-dev.org/download.php)
2. ZeroMQ: For communicating between client and server through message passing. [Download](https://github.com/zeromq/cppzmq)
3. MessagePack: It is an efficient binary serialization format which lets one exchange data among multiple languages like JSON. [Download](https://github.com/msgpack/msgpack-c/tree/cpp_master)

### Demo
[![Video](http://i3.ytimg.com/vi/kHGyrkUsC4k/maxresdefault.jpg)](https://www.youtube.com/watch?v=kHGyrkUsC4k)

### Design and Implementation Details

#### Game loop architecture
I used 'One thread per Client' architecture. Whenever a new client is created, it sends a connection request to the server and then the server replies the client with a port number. The client breaks connects to the server on the port number specified by the server. Every client is continuously listening to the events and in case of an event the client sends the event details to the server. The events are queued on the server side and the server handles the events on first come first serve basis. The server performs the calculations and sends the updated game state to all the clients.

![Image](https://viewer.diagrams.net/?highlight=0000ff&edit=_blank&layers=1&nav=1&title=Untitled%20Diagram.drawio#R7Vlbb5swFP41PDYCDJQ%2BNknbPWxapaxa9zQ5%2BCRYgzgyTkP662cHm0uAZpcsC1KlPuRc8fnO8dcTYqFJmj9wvI4%2FMQKJ5dokt9DUcl3Hc11L%2FdlkV2iubb9QLDkl2qlSzOgraKWttRtKIGs4CsYSQddNZcRWK4hEQ4c5Z9um24Ilzaeu8RJailmEk7b2KyUiLrShb1f6D0CXsXmyY2tLio2zVmQxJmxbU6E7C004Y6L4lOYTSBR4Bpci7r7HWh6Mw0r8UsCEfserGVm%2B3k%2Fjbfr56ek6v9JZXnCy0QU%2F4BSkZgb8Bbg%2BudgZODjbrAiojI6FxtuYCpitcaSsWzkAUheLNNHmBU2SCUsY38ci4kNIPKnPBGc%2FoGYJ3TkKAmnRpwEuIO8t0ynBk1MHLAXBd9JFByA%2FLEL0wIUa%2Fm3VPQfpGYxrnfO0H9YDsywzV5jKDxrW34DYbUE8SagqxrWd0%2BKLIVxEXfgGUQjzxWnwvbEb8Ja41fE1l%2Fcs%2BHr9%2BLoDxLcc2IsB2O8HGA0QYO%2FiAA76AfYGCHBwcQA77X9zLVxhRW7VviClKMFZRgucMBdtdQ1hiQnfPUvBNsI3JYx8I07zunG6M1JOxXPlKaVvNUsVpAQTU5wZSGtjOeiMrItteARvIKLrl%2BUtQbyFXHena530OxppdBwSLOhL87hd3dVPeGR0P%2FXmptrNQfLcgwEpytRR9dXnMJHfTISuDxIVOLQS7YetLPsv5q9NoV9iDph07gCqwR%2FxXC7SjUnDCV2u1BjKZsvNDI3VJaVyU73VhpQSonKMOWT0Fc%2F3%2BdTcrFVd%2B0r9seVP37rleo3WwVa5vDZmrP%2BK9XLClT1CYeA2umCWzz%2BdEuPCFosM%2Fk3f2rvb6XljhGyvzh3OyDnGHUp6BE5lfWoSLoFQvHdCOSehtFeGklA6RnSQhOIeIxQ38BpNuHw6QeegkwANn038dzY5J5vc9LNJ%2BxveMNkEHWMTJ%2FSDRhfci6eT9puPk9OJYw3pW03wThtnpA1z7i7aaL%2B3GCZteEdp48a8TDZd%2BH%2B0IcXq54TCvfpRBt39BA%3D%3D)

#### Time synchronization
The server maintains a logical clock and it starts when the server starts. Whenever a client connects to the server, the server sends this logical time to the client. The client adds this offset value to its local time so that the client clock is synchronized with the server clock. The elapsed time is calculated by the client using the formula elapsed time = ((current time - start time) / step_size) * speed + offset + 1, where step_size is the tic value of the clock.


#### Request/Reply model for communication
The communication model used by client and server is Request/Reply. Here, client connects to the server, requests info, then receives a reply.

