import { h, render } from "preact";
import { useState } from 'preact/hooks';

import Router, { Link } from 'preact-router';

import IndexPage from './pages/index';
import UpdatePage from './pages/update';
import SettingsPage from './pages/settings';

const App = () => {
  return (
  <div className="container">
    <div className="row">
      <div class="col-md-2 hidden-sm" />
      <div class="col-md-8 col-sm-12">
        <header className="sticky">
          <Link href="/" className="logo">Wordclock</Link>
          <Link href="/settings" className="button">Einstellungen</Link>
          <Link href="/update" className="button">Update</Link>
        </header>
      </div>
      <div class="col-md-2 hidden-sm" />
    </div>
    <div className="row">
      <div class="col-md-2 hidden-sm" />
      <div class="col-md-8 col-sm-12">
        <Router>
          <IndexPage path="/" />
          <UpdatePage path="/update" />
          <SettingsPage path="/settings" />
        </Router>
      </div>
      <div class="col-md-2 hidden-sm" />
    </div>
    <div className="row">
      <div class="col-md-2 hidden-sm" />
      <div class="col-md-8 col-sm-12">
        <footer className="sticky">
          <p>© 2020 Tillmann Hübner {<Link href="mailto:ruohki@gmail.com">{"ruohki@gmail.com"}</Link>}</p>
        </footer>
      </div>
      <div class="col-md-2 hidden-sm" />
    </div>
  </div>

  )
}


if (typeof window !== "undefined") {
  render(<App />, document.getElementById("root"));
}
