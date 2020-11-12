import { h  } from "preact";
import { useState } from 'preact/hooks';
import axios from 'axios';

import FilePicker from '../components/filepicker';

const Page = () => {
  const [ fileToUpload, setFileToUpload ] = useState();
  const [ percent, setPercent ] = useState(0);
  const [ uploading, setUploading ] = useState(false);

  const [ success, setSuccess ] = useState();
  const [ error, setError ] = useState();

  const uploadFile = ({ to, clear }) => {
    setUploading(true);

    const formData = new FormData()
    formData.append('file', fileToUpload)

    axios.request({
      method: "post", 
      url: to, 
      data: formData, 
      onUploadProgress: (p) => {
        setPercent(p.loaded / p.total);
      }
    }).then (data => {
      setPercent(1.0);
      setUploading(false);
      setSuccess("Die Datei wurde erfolgreich hochgeladen!");
      clear();
    }).catch(err => {
      setPercent(1.0);
      setUploading(false);
      setError("Beim Upload ist ein Fehler aufgetreten!");
      console.log(err)
    })
  }

  return ( 
    <div className="container">
      <div className="row">
        <div className="col-sm-12">
          <h4>Update <small>Firmware und UI Updates</small></h4>
          <p>Auf dieser Seite können Firmware Updates, sowie Updates dieses Frontends hochgeladen werden</p>
          <hr />
          <p>Firmware:</p>
          <FilePicker
            onChange={f => setFileToUpload(f)}
            noFile="Bitte wählen Sie eine firmware.bin aus!"
            accept=".bin"
            disabled={uploading}
            onUpload={(clear) => uploadFile({ to: '/update/firmware', clear })}
          />
          <p>Benutzeroberfläche:</p>
          <FilePicker
            onChange={f => setFileToUpload(f)}
            noFile="Bitte wählen Sie eine wordclock.gz aus!"
            accept=".gz"
            disabled={uploading}
            onUpload={(clear) => uploadFile({ to: '/update/ui', clear })}
          />
        </div>
        <div className="col-sm-12">
          {error && <mark class="secondary">{error}</mark>}
          {success && <p>{success}</p>}
        </div>
        <div className="col-sm-12">
          {uploading && <progress value={percent} max="1"></progress>}
        </div>
        <div className="col-sm-12">
          &nbsp;
        </div>
      </div>
    </div>
  )
};

export default Page