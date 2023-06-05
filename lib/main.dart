import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

const String serverUrl = "Put here you URL server";

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Schneider ',
      color: Color(0xff009e4d),
      home: MyHomePage(title: 'Pression Transmitter 4-20 mA'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  double pressureValue = 0.0;

  void fetchPressureValue() async {
    final response = await http.get(Uri.parse(serverUrl));

    if (response.statusCode == 200) {
      setState(() {
        pressureValue = double.parse(response.body);
      });
    } else {
      print('Error fetching pressure value from server');
    }
  }

  @override
  void initState() {
    fetchPressureValue();
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
        backgroundColor: Color(0xff009e4d),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              'Pressure Value: $pressureValue bar',
              style: const TextStyle(fontSize: 26, color: Color(0xff009e4d)),
            ),
            const SizedBox(height: 150),
            Image(image: AssetImage('lib/images/Schneider.png'))
          ],
        ),
      ),
    );
  }
}
