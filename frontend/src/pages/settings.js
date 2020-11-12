import { h } from "preact";
import { useState, useEffect } from 'preact/hooks';
import { ChromePicker } from 'react-color'
import axios from 'axios';


const Page = () => {
  const [ color, setColor ] = useState({ rgb: { r: 255, g: 0, b: 0, a: 1}});
  const [ brightness, _setBrightness ] = useState(100);

  const setBrightness = (e) => {
    const val = parseInt(e.target.value) ?? 0;

    if (val > 255) return _setBrightness(255);
    if (val < 0) return _setBrightness(0);
    _setBrightness(val);
  }
console.log(color);
  useEffect(() => {
    axios.request({
      method: "get", 
      url: "/color", 
    }).then (data => {
      const { r = 255, g = 0, b = 0, brightness = 100 } = data.data;
      console.log("Data", data.data)
      
      setColor({ rgb: { r, g, b, a: 1}, source: "rgb"});
      _setBrightness(brightness);

    }).catch(err => {
      console.log(err)
    })
  }, [ setColor, _setBrightness ])

  const sendToClock = () => {
    axios.request({
      method: "post", 
      url: "/color", 
      params: {
        r: color.rgb.r,
        g: color.rgb.g,
        b: color.rgb.b,
        bri: brightness
      }, 
    }).then (data => {
      console.log("Done");
    }).catch(err => {
      console.log(err)
    })
  }

  return (
     <div className="container">
      <div className="row">
        <div className="col-sm-12">
          <h4>Einstellungen</h4>
          <p>Auf dieser Seite können Einstellungen der Uhr vorgenommen werden</p>
          <hr />
          <div className="row">
            <div className="col-sm-12">
              {console.log(color)}
              <ChromePicker disableAlpha color={color.rgb} onChange={setColor} />
              <div style={{marginTop: 10}}>
                Helligkeit: <input type="range" min={0} max={255} onChange={setBrightness} value={brightness} />{Math.round(brightness / 255 * 100)}%
              </div>
            </div>
          </div>
          <button style={{ float: "left"}} onClick={sendToClock}>Speichern</button>
          <div style={{marginBottom: 10}} />
        </div>
      </div>
    </div>
  )
};

export default Page